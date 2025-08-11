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
        stage('Run Pipeline') {
            steps {
                script {
                    try {
                        // ===== Stage 1: Environment Setup =====
                        echo 'Setting up environment...'
                        sh 'bash -c "source ./env_setup.sh && env"'

                        // ===== Stage 2: Clean & Build =====
                        echo 'Cleaning and building...'
                        sh 'make clean'
                        sh 'make'

                        // ===== Stage 3: Boot and Flash =====
                        echo 'Flashing board and capturing serial output...'
                        sh 'mkdir -p ${BUILD_DIR}'
                        sh 'chmod +x run.sh'
                        sh './run.sh'
                        sh 'cp serial_output.log ${RUN_LOG}'

                        // ===== Stage 4: Sanity Test =====
                        echo 'Running Sanity Test on serial log...'
                        def serialLog = readFile("${RUN_LOG}")
                        if (serialLog.contains("Hello") || serialLog.contains("Boot") || serialLog.contains("Welcome")) {
                            echo "Sanity Test Passed: Boot log detected"
                        } else {
                            error("Sanity Test Failed: Expected boot message not found.")
                        }

                        // ===== Stage 5: Display Serial Output =====
                        echo "====== Serial Output ======"
                        def output = readFile("${RUN_LOG}").trim()
                        echo output

                        // ===== Gather Info for Email =====
                        env.COMMIT_AUTHOR = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                        env.GIT_COMMIT_MSG = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                        env.JOB_NAME_ONLY = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME
                        env.RUN_LOG_CONTENT = output

                        // ===== Send Success Email =====
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

                    } catch (err) {
                        // ===== Gather Info for Failure Email =====
                        env.COMMIT_AUTHOR = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                        env.GIT_COMMIT_MSG = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()
                        env.JOB_NAME_ONLY = env.JOB_NAME.contains('/') ? env.JOB_NAME.tokenize('/')[1] : env.JOB_NAME
                        def serialLogPath = "${RUN_LOG}"
                        env.RUN_LOG_CONTENT = fileExists(serialLogPath) ? readFile(serialLogPath).trim() : 'Serial output log not found.'

                        // ===== Send Failure Email =====
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

                        // Fail the pipeline
                        error("Pipeline failed: ${err}")
                    }
                }
            }
        }
    }
}
