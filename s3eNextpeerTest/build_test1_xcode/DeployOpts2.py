# coding=utf-8

###### Options ######

options={}

options["<config>"]=ur'Default'
options["<os>"]=ur'iphone'
options["appdata"]=ur'/Users/danielshir/.config/marmalade/DeployTool'
options["build"]=ur'ARM GCC Debug'
options["cmdline"]=['/Developer/Marmalade/5.2/s3e/makefile_builder/mkb.py', '--buildenv=xcode', '/Users/danielshir/Work/InnoBell/s3eNextpeerTest/test1.mkb', '--deploy-only']
options["configlist"]=ur'Default ,'
options["deploymode"]=ur'Package'
options["device"]=ur'"{"localdir}/Deploy.py" device "{"tempdir}/DeployOpts.py" {hasmkb}'
options["dir"]=ur'/Users/danielshir/Work/InnoBell/s3eNextpeerTest/build_test1_xcode'
options["folder"]=ur'"{"localdir}/Deploy.py" folder "{"tempdir}/DeployOpts.py" {hasmkb}'
options["hasmkb"]=ur'nomkb'
options["helpfile"]=ur'../docs/Deployment.chm'
options["helppage"]=ur'0'
options["lastdir"]=ur'/Users/danielshir/Work/InnoBell/s3eNextpeerTest/build_test1_xcode'
options["mkb"]=ur'/Users/danielshir/Work/InnoBell/s3eNextpeerTest/test1.mkb'
options["mkbdir"]=ur'/Users/danielshir/Work/InnoBell/s3eNextpeerTest'
options["mkbfile"]=ur'test1.mkb'
options["outdir"]=ur'/Users/danielshir/Work/InnoBell/s3eNextpeerTest/build_test1_xcode'
options["resdir"]=ur'/Developer/Marmalade/5.2/Applications/DeployTool.app/Contents/Resources/'
options["s3edir"]=ur'/Developer/Marmalade/5.2/s3e/'
options["stage"]=ur'build'
options["target"]=ur'test1'
options["task"]=ur'Default'
options["tasktype"]=ur'Package'

###### Tasks ######

tasks=[]

### Task Default:iphone ###

t={}
tasks.append(t)
t["tasktype"]="Package"
t["<config>"]="Default"
t["os"]="iphone"
t["endDir"]="/Users/danielshir/Work/InnoBell/s3eNextpeerTest/build_test1_xcode/deployments/default/iphone/debug"
