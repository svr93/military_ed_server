iptables -I INPUT -p tcp --dport 80 -m state --state NEW -j ACCEPT
mainPath=$(pwd)
cd applications/main/app/api/info.json
. build.sh
cd $mainPath
node server.js
