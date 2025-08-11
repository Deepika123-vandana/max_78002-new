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
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh 'bash -c "source ./env_setup.sh && env"'
                }
            }
        }

        stage('Clean & Build') {
            steps {
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh 'make clean'
                    sh 'make'
                }
            }
        }

        stage('Boot and Flash') {
            steps {
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh 'mkdir -p ${BUILD_DIR}'
                    sh 'chmod +x run.sh'
                    sh './run.sh'
                    sh 'cp serial_output.log ${RUN_LOG} || echo "Serial output log not found." > ${RUN_LOG}'
                }
            }
        }

        stage('Sanity Test') {
            steps {
                echo '=== Sanity Test (Placeholder) ==='
                echo 'No tests implemented yet.'
            }
        }

        stage('Display Serial Output') {
            steps {
                script {
                    def output = fileExists("${RUN_LOG}") ? readFile("${RUN_LOG}").trim() : "Serial output log not found."
                    echo "====== Serial Output ======"
                    echo output
                    env.RUN_LOG_CONTENT = output
                }
            }
        }

        stage('Send Email') {
            steps {
                script {
                    env.COMMIT_AUTHOR = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                    env.GIT_COMMIT_MSG = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                    env.JOB_NAME_ONLY = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME

                    def subjectColor = currentBuild.result == 'FAILURE' ? 'red' : 'green'
                    def subjectText = currentBuild.result == 'FAILURE' ? 'Build Failure' : 'Build Success'

                    emailext(
                        subject: "Jenkins ${subjectText} - ${env.JOB_NAME_ONLY} #${env.BUILD_NUMBER}",
                        body: """
                            <h2 style="color: ${subjectColor};">Build Status: ${currentBuild.result}</h2>
                            <p><strong>Job Name:</strong> ${env.JOB_NAME_ONLY}</p>
                            <p><strong>Build Number:</strong> #${env.BUILD_NUMBER}</p>
                            <p><strong>Branch Name:</strong> ${env.GIT_BRANCH}</p>
                            <p><strong>Commit Author:</strong> ${env.COMMIT_AUTHOR}</p>
                            <p><strong>Commit Message:</strong> ${env.GIT_COMMIT_MSG}</p>
                            <p><strong>Email Sent To:</strong> ${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}</p>
                            <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console">${env.BUILD_URL}console</a></p>
                            <hr>
                            <h3>Test Output:</h3>
                            <pre>${env.RUN_LOG_CONTENT}</pre>
                            <br>
                            Regards,<br>
                            Jenkins
                        """,
                        mimeType: 'text/html',
                        to: "${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}",
                        from: "sriram.ungatla@vconnecttech.in"
                    )
                }
            }
        }
    }
}
