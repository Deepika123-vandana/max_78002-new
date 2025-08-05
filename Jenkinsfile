pipeline {
    agent any

    environment {
        MAXIM_PATH = "/home/admin1/MaximSDK"
        PATH = "${env.PATH}:${MAXIM_PATH}/Tools/OpenOCD/bin"
        BUILD_DIR = "${WORKSPACE}/build"
        RUN_LOG = "${BUILD_DIR}/run_output.log"
        TEAM_LEAD_EMAIL = "sriram.ungatla@vconnectech.in,deepika.vandana@vconnectech.in"
    }

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

        stage('Run Tests') {
            steps {
                echo 'Running tests...'
                sh 'mkdir -p ${BUILD_DIR}'
                sh 'chmod +x run.sh'
                sh './run.sh | tee ${RUN_LOG}'
            }
        }
    }

    post {
        always {
            script {
                env.COMMIT_AUTHOR = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                env.GIT_COMMIT_MSG = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                env.JOB_NAME_ONLY = env.JOB_NAME.tokenize('/')[1]
                env.RUN_LOG_CONTENT = sh(script: "tail -n 100 '${env.RUN_LOG}' || echo 'Run output not found.'", returnStdout: true).trim()
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
                        <p><strong>Commit Authors:</strong> ${env.COMMIT_AUTHOR}</p>
                        <p><strong>Commit Message:</strong> ${env.GIT_COMMIT_MSG}</p>
                        <p><strong>Email Sent To:</strong> ${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}</p>
                        <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console" target="_blank">${env.BUILD_URL}console</a></p>

                        <hr style="border: none; border-top: 1px solid #ccc; margin: 20px 0;">

                        <h3>Test Output:</h3>
                        <pre style="background: #f7f7f7; border: 1px solid #ddd; padding: 10px; font-family: Consolas, monospace; font-size: 14px; overflow-x: auto;">${env.RUN_LOG_CONTENT}</pre>

                        <p style="margin-top: 30px; font-size: 14px;">
                            Regards,<br>
                            Jenkins
                        </p>
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
                        <p><strong>Commit Authors:</strong> ${env.COMMIT_AUTHOR}</p>
                        <p><strong>Commit Message:</strong> ${env.GIT_COMMIT_MSG}</p>
                        <p><strong>Email Sent To:</strong> ${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}</p>
                        <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console" target="_blank">${env.BUILD_URL}console</a></p>

                        <hr style="border: none; border-top: 1px solid #ccc; margin: 20px 0;">

                        <h3>Test Output:</h3>
                        <pre style="background: #f7f7f7; border: 1px solid #ddd; padding: 10px; font-family: Consolas, monospace; font-size: 14px; overflow-x: auto;">${env.RUN_LOG_CONTENT}</pre>

                        <p style="margin-top: 30px; font-size: 14px;">
                            Regards,<br>
                            Jenkins
                        </p>
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
