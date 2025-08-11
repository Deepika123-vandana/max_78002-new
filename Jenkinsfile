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
                sh 'echo Setting up environment...'
            }
        }

        stage('Clean & Build') {
            steps {
                sh '''
                    echo Cleaning build directory...
                    rm -rf ${BUILD_DIR}
                    mkdir -p ${BUILD_DIR}
                    echo Building project...
                    # your actual build commands go here
                '''
            }
        }

        stage('Boot and Flash') {
            steps {
                sh '''
                    set -e
                    mkdir -p ${BUILD_DIR}
                    chmod +x run.sh
                    ./run.sh | tee ${RUN_LOG}
                '''
            }
        }

        stage('Sanity Test') {
            when {
                expression { currentBuild.currentResult == 'SUCCESS' }
            }
            steps {
                echo "=== Sanity Test Stage ==="
                echo "No tests implemented yet."
            }
        }
    }

    post {
        success {
            emailext (
                subject: "SUCCESS: Job '${JOB_NAME} [${BUILD_NUMBER}]'",
                body: "Pipeline succeeded.\nCheck console: ${BUILD_URL}",
                to: "deepika.vandana@vconnectech.in,sriram.ungatla@vconnectech.in"
            )
        }
        failure {
            emailext (
                subject: "FAILURE: Job '${JOB_NAME} [${BUILD_NUMBER}]'",
                body: "Pipeline failed.\nCheck console: ${BUILD_URL}",
                to: "deepika.vandana@vconnectech.in,sriram.ungatla@vconnectech.in"
            )
        }
    }
}
