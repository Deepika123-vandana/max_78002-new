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
                sh 'bash -c "source ./env_setup.sh && env"'
            }
        }

        stage('Clean & Build') {
            steps {
                sh 'make clean'
                sh 'make'
            }
        }

        stage('Boot and Flash') {
            steps {
                script {
                    sh "mkdir -p ${BUILD_DIR}"
                    sh "chmod +x run.sh"
                    sh "./run.sh"
                    sh "cp serial_output.log ${RUN_LOG} || echo 'Serial output log not found.' > ${RUN_LOG}"
                }
            }
        }

        stage('Sanity Test') {
            when {
                expression { currentBuild.resultIsBetterOrEqualTo('SUCCESS') }
            }
            steps {
                echo 'Sanity Test stage (currently empty)'
            }
        }

        stage('Display Serial Output & Send Email') {
            steps {
                script {
                    def buildStatus = currentBuild.result ?: 'SUCCESS'

                    // Read serial log if exists
                    def output = fileExists(RUN_LOG) ? readFile(RUN_LOG).trim() : 'Serial output log not found.'
                    echo "====== Serial Output ======"
                    echo output

                    // Git commit info
                    env.COMMIT_AUTHOR = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                    env.GIT_COMMIT_MSG = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                    env.JOB_NAME_ONLY = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME

                    // Email colors & subject
                    def subjectColor = buildStatus == 'FAILURE' ? 'red' : 'green'
                    def subjectText = buildStatus == 'FAILURE' ? 'Build Failure' : 'Build Success'

                    // Send email
                    emailext(
                        subject: "Jenkins ${subjectText} - ${env.JOB_NAME_ONLY} #${env.BUILD_NUMBER}",
                        body: """
                            <h2 style="color: ${subjectColor};">Build Status: ${buildStatus}</h2>
                            <p><strong>Job Name:</strong> ${env.JOB_NAME_ONLY}</p>
                            <p><strong>Build Number:</strong> #${env.BUILD_NUMBER}</p>
                            <p><strong>Branch Name:</strong> ${env.GIT_BRANCH}</p>
                            <p><strong>Commit Author:</strong> ${env.COMMIT_AUTHOR}</p>
                            <p><strong>Commit Message:</strong> ${env.GIT_COMMIT_MSG}</p>
                            <p><strong>Email Sent To:</strong> ${env.COMMIT_AUTHOR}, ${TEAM_LEAD_EMAIL}</p>
                            <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console">${env.BUILD_URL}console</a></p>
                            <hr>
                            <h3>Test Output:</h3>
                            <pre>${output}</pre>
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
