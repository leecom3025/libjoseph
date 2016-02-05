
usage() {
  echo "sudo ./sub_flows.sh [num subflows]"
}

sh -c "echo $1 > /sys/module/mptcp_fullmesh/parameters/num_subflows"
cat /sys/module/mptcp_fullmesh/parameters/num_subflows
