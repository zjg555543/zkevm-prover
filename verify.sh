cd ../pil-stark/

ZKEVM_PROVER_DIR=../zkevm-prover

verkey=$(tr -d '[:blank:]' < ${ZKEVM_PROVER_DIR}/config/recursive2/recursive2.verkey.json | awk -F "," '{if(NR==3) print "[\""$1"\"," ; else if (NR == 6) print "\""$1"\"]"; else if(NR>=3 && NR<7) print "\""$1"\","}')

jq --argjson groupInfo "$(echo $verkey)" '. + $groupInfo' $(ls -t ${ZKEVM_PROVER_DIR}/runtime/output/*.batch_proof.public.json | head -n1) > $(ls -t ${ZKEVM_PROVER_DIR}/runtime/output/*.batch_proof.public.json | head -n1).tmp && mv $(ls -t ${ZKEVM_PROVER_DIR}/runtime/output/*.batch_proof.public.json | head -n1).tmp $(ls -t ${ZKEVM_PROVER_DIR}/runtime/output/*.batch_proof.public.json | head -n1)

node src/main_verifier.js -p ${ZKEVM_PROVER_DIR}/config/recursive1/recursive1.pil -s ${ZKEVM_PROVER_DIR}/config/recursive1/recursive1.starkstruct.json -o $(ls -t ${ZKEVM_PROVER_DIR}/runtime/output/*.batch_proof.proof.json | head -n1) -b $(ls -t ${ZKEVM_PROVER_DIR}/runtime/output/*.batch_proof.public.json | head -n1) -v ${ZKEVM_PROVER_DIR}/config/recursive1/recursive1.verkey.json
