sudo dscl . -create /groups/docker
sudo dscl . -append /groups/docker PrimaryGroupID 5000
sudo dscl . -append /groups/docker Password "*"
sudo dscl . -append /groups/docker GroupMembership $USER
newgrp docker

