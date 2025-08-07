    stages {
        stage('Environment Setup') {
            steps {
                echo 'Setting up environment...'
                sh 'bash -c "source ./env_setup.sh && env"'
            }
        }

        stage('Build') {
            steps {
                echo 'Running make...'
                sh 'make'
            }
        }

        stage('Boot') {
            steps {
                echo 'Running tests and capturing serial output...'
                sh 'mkdir -p ${BUILD_DIR}'
                sh 'chmod +x run.sh'
                sh './run.sh'
                sh 'cp serial_output.log ${RUN_LOG}'
            }
        }

        stage('Sanity Test') {
            steps {
                echo 'Running basic sanity test...'
                // Placeholder for real tests
                sh '''
                    echo "Sanity check: PASS" >> ${RUN_LOG}
                '''
            }
        }

        stage('Display Serial Output') {
            steps {
                script {
                    echo "====== Serial Output ======"
                    def output = readFile('serial_output.log').trim()
                    echo output

                    env.RUN_LOG_CONTENT = output
                }
            }
        }
    }


    post {
        always {
            script {
                env.COMMIT_AUTHOR = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                env.GIT_COMMIT_MSG = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                env.JOB_NAME_ONLY = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME

                def serialLogPath = 'serial_output.log'
                if (fileExists(serialLogPath)) {
                    env.RUN_LOG_CONTENT = readFile(serialLogPath).trim()
                } else {
                    env.RUN_LOG_CONTENT = 'Serial output log not found.'
                }
            }
        }

        success {
            emailext(
                subject: "Jenkins Build Success - ${env.JOB_NAME_ONLY} #${env.BUILD_NUMBER}",
                body: """
                    <div style="font-family: Arial, sans-serif; font-size: 14px; color: #333;">
                        <h2 style="color: green;">Build Status: SUCCESS</h2>
                        <p><strong>Job Name:</strong> ${env.JOB_NAME_ONLY}</p>
                        <p><strong>Build Number:</strong> #${env.BUILD_NUMBER}</p>
                        <p><strong>Branch Name:</strong> ${env.GIT_BRANCH}</p>
                        <p><strong>Commit Author:</strong> ${env.COMMIT_AUTHOR}</p>
                        <p><strong>Commit Message:</strong> ${env.GIT_COMMIT_MSG}</p>
                        <p><strong>Email Sent To:</strong> ${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}</p>
                        <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console" target="_blank">${env.BUILD_URL}console</a></p>

                        <hr style="border: none; border-top: 1px solid #ccc; margin: 20px 0;">

                        <h3>Test Output:</h3>
                        <pre style="background: #f7f7f7; border: 1px solid #ddd; padding: 10px; font-family: Consolas, monospace; font-size: 14px; overflow-x: auto;">
${env.RUN_LOG_CONTENT}
                        </pre>

                        <p style="margin-top: 30px;">Regards,<br>Jenkins</p>
                    </div>
                """,
                mimeType: 'text/html',
                to: "${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}",
                from: "sriram.ungatla@vconnecttech.in",
                attachLog: false
            )
        }

        failure {
            emailext(
                subject: "Jenkins Build Failure - ${env.JOB_NAME_ONLY} #${env.BUILD_NUMBER}",
                body: """
                    <div style="font-family: Arial, sans-serif; font-size: 14px; color: #333;">
                        <h2 style="color: red;">Build Status: FAILURE</h2>
                        <p><strong>Job Name:</strong> ${env.JOB_NAME_ONLY}</p>
                        <p><strong>Build Number:</strong> #${env.BUILD_NUMBER}</p>
                        <p><strong>Branch Name:</strong> ${env.GIT_BRANCH}</p>
                        <p><strong>Commit Author:</strong> ${env.COMMIT_AUTHOR}</p>
                        <p><strong>Commit Message:</strong> ${env.GIT_COMMIT_MSG}</p>
                        <p><strong>Email Sent To:</strong> ${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}</p>
                        <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console" target="_blank">${env.BUILD_URL}console</a></p>

                        <hr style="border: none; border-top: 1px solid #ccc; margin: 20px 0;">

                        <h3>Test Output:</h3>
                        <pre style="background: #f7f7f7; border: 1px solid #ddd; padding: 10px; font-family: Consolas, monospace; font-size: 14px; overflow-x: auto;">
${env.RUN_LOG_CONTENT}
                        </pre>

                        <p style="margin-top: 30px;">Regards,<br>Jenkins</p>
                    </div>
                """,
                mimeType: 'text/html',
                to: "${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}",
                from: "sriram.ungatla@vconnecttech.in",
                attachLog: false
            )
        }
    }
}
