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

        stage('Display Serial Output and Email') {
            steps {
                script {
                    // Read the serial log
                    def runLogContent = fileExists(RUN_LOG) ? readFile(RUN_LOG).trim() : "Serial output log not found."

                    echo "====== Serial Output ======"
                    echo runLogContent

                    // Get git info
                    def commitAuthor = sh(script: "git log -1 --pretty=format:%ae", returnStdout: true).trim()
                    def gitCommitMsg = sh(script: "git log -1 --pretty=format:%s", returnStdout: true).trim()

                    // Determine build status safely
                    def buildStatus = currentBuild.result ?: 'SUCCESS'
                    def branch = env.BRANCH_NAME ?: env.GIT_BRANCH ?: 'main'

                    // Send email
                    emailext(
                        subject: "Jenkins Build ${buildStatus} - ${branch} #${env.BUILD_NUMBER}",
                        body: """
                        Build Status: ${buildStatus}
                        
                        Job Name: ${env.JOB_NAME}
                        Build Number: #${env.BUILD_NUMBER}
                        Branch Name: ${branch}
                        Commit Author: ${commitAuthor}
                        Commit Message: ${gitCommitMsg}
                        Email Sent To: ${TEAM_LEAD_EMAIL}
                        
                        Console Output: ${env.BUILD_URL}console
                        Serial Output:
                        
                        ${runLogContent}
                        
                        Regards,
                        Jenkins
                        """
                        )

                    // Revert last commit if build failed on main
                    if (buildStatus == 'FAILURE' && branch.endsWith("main")) {
                        echo "Build failed on main branch. Starting revert process..."

                        withCredentials([string(credentialsId: 'All_projects', variable: 'GITHUB_TOKEN')]) {
                            sh '''
                                set -e
                                git config user.name "Deepika123-vandana"
                                git config user.email "deepika.vandana@vconnectech.in"

                                echo "Ensuring we are on latest main..."
                                git fetch https://$GITHUB_TOKEN@github.com/Deepika123-vandana/max_78002-new.git main
                                git checkout main
                                git reset --hard FETCH_HEAD

                                echo "Reverting last commit..."
                                git revert --no-edit HEAD

                                echo "Pushing revert to remote..."
                                git push https://$GITHUB_TOKEN@github.com/Deepika123-vandana/max_78002-new.git main
                            '''
                        }
                    } else {
                        echo "No revert needed. Build status: ${buildStatus}, Branch: ${branch}"
                    }
                }
            }
        }
    }
}
