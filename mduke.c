export ZONE=
curl -LO raw.githubusercontent.com/QUICK-GCP-LAB/2-Minutes-Labs-Solutions/main/Managing%20Deployments%20Using%20Kubernetes%20Engine/gsp053.sh

sudo chmod +x gsp053.sh

./gsp053.sh

gsutil -m cp -r gs://spls/gsp053/orchestrate-with-kubernetes .
cd orchestrate-with-kubernetes/kubernetes
gcloud container clusters create bootcamp \
  --machine-type e2-small \
  --num-nodes 3 \
  --scopes "https://www.googleapis.com/auth/projecthosting,storage-rw"

ask 2. Create a deployment
vi deployments/auth.yaml
i
...
containers:
- name: auth
  image: "kelseyhightower/auth:1.0.0"
...
kubectl create -f deployments/auth.yaml
kubectl create -f services/auth.yaml
kubectl create -f deployments/hello.yaml
kubectl create -f services/hello.yaml
kubectl create secret generic tls-certs --from-file tls/
kubectl create configmap nginx-frontend-conf --from-file=nginx/frontend.conf
kubectl create -f deployments/frontend.yaml
kubectl create -f services/frontend.yaml
curl -ks https://`kubectl get svc frontend -o=jsonpath="{.status.loadBalancer.ingress[0].ip}"`
kubectl scale deployment hello --replicas=3

Task 3. Rolling update
kubectl edit deployment hello
...
containers:
  image: kelseyhightower/hello:2.0.0
...
kubectl rollout pause deployment/hello
kubectl rollout resume deployment/hello
kubectl rollout undo deployment/hello

Task 4. Canary deployments
cat deployments/hello-canary.yaml
kubectl create -f deployments/hello-canary.yaml


ask 5. Blue-green deployments
kubectl apply -f services/hello-blue.yaml
kubectl create -f deployments/hello-green.yaml
kubectl apply -f services/hello-green.yaml
kubectl apply -f services/hello-blue.yaml
