#!/bin/bash

VERSION=0.25.0
NAMESPACE=consul

DEPLOYMENT_NAME=consul

# get secrets
. ~/.config/stack

# Check for namespace
kubectl get namespace ${NAMESPACE}
NAMESPACE_FOUND=$?

if [ $NAMESPACE_FOUND -ne 0 ]; then
  kubectl create namespace ${NAMESPACE}
fi

# Add repo and update
helm repo add hashicorp https://helm.releases.hashicorp.com
helm repo update

# Check for deployment
helm -n ${NAMESPACE} status ${DEPLOYMENT_NAME};
HELM_DEPLOY_FOUND=$?

HELM_ACTION=install
if [ $HELM_DEPLOY_FOUND -eq 0 ]; then
  HELM_ACTION=upgrade
fi

# Run helm command
helm ${HELM_ACTION} ${DEPLOYMENT_NAME} \
    --namespace ${NAMESPACE} \
    --version ${VERSION} \
    --set agentToken=${AGENT_TOKEN} \
    --values consul-values.yaml \
    hashicorp/consul
