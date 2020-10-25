# K3S cluster "stack"
OS: ubuntu 20.04 LTS arm64

## Setup

| IP         | Hostname         | Hardware | Disk Size |
| ---------- | ---------------- | -------- | --------- |
| 10.1.70.40 | stack-database   | VIP      |           |
| 10.1.70.41 | stack-database-1 | 3B+      | 64G       |
| 10.1.70.42 | stack-database-2 | 3B+      | 64G       |
| 10.1.70.43 | stack-witness-1  | 3B       | 16G       |
| 10.1.70.48 | stack-leader-2   | 3B+      | 256G      |
| 10.1.70.49 | stack-leader-1   | 3B+      | 256G      |
| 10.1.70.50 | stack-leader     | VIP      |           |
| 10.1.70.51 | stack-worker-1   | 4B (8G)  | 256G      |
| 10.1.70.52 | stack-worker-2   | 4B (8G)  | 256G      |
| 10.1.70.53 | stack-worker-3   | 4B (8G)  | 256G      |
