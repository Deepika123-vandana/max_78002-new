pipeline {
    agent any

    environment {
        MAXIM_PATH = "/home/admin1/MaximSDK"
        PATH = "${env.PATH}:${MAXIM_PATH}/Tools/OpenOCD/bin"
        BUILD_DIR = "${WORKSPACE}/build"
        RUN_LOG = "${BUILD_DIR}/run_output.log"
        TEAM_LEAD_EMAIL = "deepika.vandana@vconnectech.in"
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
                    sh 'make'
                }
            }
        }

        stage('Boot and Flash') {
            steps {
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh """
                        mkdir -p ${BUILD_DIR}
                        chmod +x run.sh
                        ./run.sh
                    """
                }
                sh """
                    if [ -f serial_output.log ]; then
                        cp serial_output.log ${RUN_LOG}
                    else
                        echo "Serial output log not found." > ${RUN_LOG}
                    fi
                """
            }
        }

        stage('Sanity Test - GPIO') {
            when {
                expression { currentBuild.result == null || currentBuild.result == 'SUCCESS' }
            }
            steps {
                script {
                    echo "=== Running GPIO Sanity Test ==="
                    if (fileExists(RUN_LOG)) {
                        def runLogContent = readFile(RUN_LOG).trim()
                        echo "=== GPIO Test Serial Log ==="
                        echo runLogContent

                        if (runLogContent.contains("All Test cases of GPIO PASSED!")) {
                            echo "Sanity Check PASSED: GPIO tests succeeded."
                        } else {
                            error "Sanity Check FAILED: GPIO tests did not pass. Check serial log."
                        }
                    } else {
                        error "Sanity Check FAILED: Run log file not found."
                    }
                }
            }
        }

        stage('Display Serial Output and email') {
            steps {
                script {
                    def runLogFile = "${RUN_LOG}"
                    def runLogContent = fileExists(runLogFile) ? readFile(runLogFile).trim() : "Serial output log not found."

                    echo "====== Serial Output ======"
                    echo runLogContent

                    def commitAuthor = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                    def gitCommitMsg = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                    def jobNameOnly = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME

                    // normalize build result
                    def buildStatus = currentBuild.result ?: 'SUCCESS'
                    def subjectColor = buildStatus == 'FAILURE' ? 'red' : 'green'
                    def subjectText = buildStatus == 'FAILURE' ? 'Build Failure' : 'Build Success'

                    emailext(
                        subject: "Jenkins ${subjectText} - ${jobNameOnly} #${env.BUILD_NUMBER}",
                        body: """
                            <h2 style="color: ${subjectColor};">Build Status: ${buildStatus}</h2>
                            <p><strong>Job Name:</strong> ${jobNameOnly}</p>
                            <p><strong>Build Number:</strong> #${env.BUILD_NUMBER}</p>
                            <p><strong>Branch Name:</strong> ${env.GIT_BRANCH}</p>
                            <p><strong>Commit Author:</strong> ${commitAuthor}</p>
                            <p><strong>Commit Message:</strong> ${gitCommitMsg}</p>
                            <p><strong>Email Sent To:</strong> ${commitAuthor}, ${TEAM_LEAD_EMAIL}</p>
                            <p><strong>Console Output:</strong> <a href="${env.BUILD_URL}console">${env.BUILD_URL}console</a></p>
                            <hr>
                            <h3>Serial Output:</h3>
                            <pre>${runLogContent}</pre>
                            <br>
                            Regards,<br>
                            Jenkins
                        """,
                        mimeType: 'text/html',
                        to: "${commitAuthor}, ${TEAM_LEAD_EMAIL}",
                        from: "sriram.ungatla@vconnecttech.in"
                    )
                }
            }
        }
    }

    


}
