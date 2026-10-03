#! /bin/bash
#
# Corvus v5 Bench wrapper
#

case $1 in
    version|--version)
        dotnet=$(dotnet --list-sdks | cut -d' ' -f1 | head -1)
        corvus=$(jq -r '.projects[].frameworks[].topLevelPackages[]|select(.id=="Corvus.Text.Json")|.resolvedVersion' /app/versions.json)
        read jmc_version < /app/.jmc_version
        echo "Corvus $corvus (.NET SDK $dotnet, JMC $jmc_version)"
        ;;
    *) 
        /app/publish/corvus-bench "$@"
        ;;
esac
