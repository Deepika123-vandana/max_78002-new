pipeline {
    agent any

    environment {
        MAXIM_PATH = "/home/admin1/MaximSDK"
        PATH = "${env.PATH}:${MAXIM_PATH}/Tools/OpenOCD/bin"
        BUILD_DIR = "${WORKSPACE}/build"
        RUN_LOG = "${BUILD_DIR}/run_output.log"
        TEAM_LEAD_EMAIL = "sriram.ungatla@vconnectech.in, deepika.vandana@vconnectech.in"
    }

    stages {
        stage('Environment Setup') {
            steps {
                githubNotify context: 'Environment Setup', status: 'PENDING', description: 'Setting up environment'
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh 'bash -c "source ./env_setup.sh && env"'
                }
                script {
                    if (currentBuild.result == 'FAILURE') {
                        githubNotify context: 'Environment Setup', status: 'FAILURE', description: 'Env setup failed'
                    } else {
                        githubNotify context: 'Environment Setup', status: 'SUCCESS', description: 'Env setup passed'
                    }
                }
            }
        }

        stage('Clean & Build') {
            steps {
                githubNotify context: 'Build', status: 'PENDING', description: 'Build started'
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh 'make'
                }
                script {
                    if (currentBuild.result == 'FAILURE') {
                        githubNotify context: 'Build', status: 'FAILURE', description: 'Build failed'
                    } else {
                        githubNotify context: 'Build', status: 'SUCCESS', description: 'Build passed'
                    }
                }
            }
        }

        stage('Boot and Flash') {
            steps {
                githubNotify context: 'Boot & Flash', status: 'PENDING', description: 'Boot and flashing started'
                catchError(buildResult: 'FAILURE', stageResult: 'FAILURE') {
                    sh """
                        mkdir -p ${BUILD_DIR}
                        chmod +x run.sh
                        //./run.sh
                    """
                }
                sh """
                    if [ -f serial_output.log ]; then
                        cp serial_output.log ${RUN_LOG}
                    else
                        echo "Serial output log not found." > ${RUN_LOG}
                    fi
                """
                script {
                    if (currentBuild.result == 'FAILURE') {
                        githubNotify context: 'Boot & Flash', status: 'FAILURE', description: 'Boot/Flash failed'
                    } else {
                        githubNotify context: 'Boot & Flash', status: 'SUCCESS', description: 'Boot/Flash passed'
                    }
                }
            }
        }

        stage('Sanity Test - GPIO') {
            when {
                expression { currentBuild.result == null || currentBuild.result == 'SUCCESS' }
            }
            steps {
                githubNotify context: 'Sanity Test - GPIO', status: 'PENDING', description: 'GPIO sanity test started'
                script {
                    echo "=== Running GPIO Sanity Test ==="
                    if (fileExists(RUN_LOG)) {
                        def runLogContent = readFile(RUN_LOG).trim()
                        echo runLogContent

                        if (runLogContent.contains("All Test cases of GPIO PASSED!")) {
                            githubNotify context: 'Sanity Test - GPIO', status: 'SUCCESS', description: 'GPIO tests passed'
                        } else {
                            githubNotify context: 'Sanity Test - GPIO', status: 'FAILURE', description: 'GPIO tests failed'
                            error "Sanity Check FAILED"
                        }
                    } else {
                        githubNotify context: 'Sanity Test - GPIO', status: 'FAILURE', description: 'Run log missing'
                        error "Run log missing"
                    }
                }
            }
        }

        stage('Display Serial Output and email') {
            steps {
                script {
                    def runLogFile = "${RUN_LOG}"
                    def runLogContent = fileExists(runLogFile) ? readFile(runLogFile).trim() : "Serial output log not found."

                    echo runLogContent

                    def commitAuthor = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                    def gitCommitMsg = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                    def jobNameOnly = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME

                    // normalize build result
                    def buildStatus = currentBuild.result ?: 'SUCCESS'

                    // final GitHub status
                    githubNotify context: 'Overall Pipeline', status: buildStatus, description: "Pipeline finished with ${buildStatus}"

                    emailext(
                        subject: "Jenkins ${buildStatus} - ${jobNameOnly} #${env.BUILD_NUMBER}",
                        body: """
                            <h2>Build Status: ${buildStatus}</h2>
                            <p><strong>Commit:</strong> ${gitCommitMsg}</p>
                            <pre>${runLogContent}</pre>
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
