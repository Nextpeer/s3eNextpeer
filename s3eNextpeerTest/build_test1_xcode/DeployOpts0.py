# coding=utf-8

###### Options ######

options={}

options["<config>"]=ur'Default'
options["<os>"]=ur'iphone'
options["appdata"]=ur'/Users/danielshir/.config/marmalade/DeployTool'
options["build"]=ur'ARM GCC Release'
options["cmdline"]=['/Developer/Marmalade/5.2/s3e/makefile_builder/mkb.py', '--buildenv=xcode', '/Developer/Marmalade/5.2/extensions/s3eNextpeer/s3eNextpeerTest/test1.mkb', '--deploy-only']
options["configlist"]=ur'Default ,'
options["device"]=ur'"{"localdir}/Deploy.py" device "{"tempdir}/DeployOpts.py" {hasmkb}'
options["dir"]=ur'/Developer/Marmalade/5.2/extensions/s3eNextpeer/s3eNextpeerTest/build_test1_xcode'
options["folder"]=ur'"{"localdir}/Deploy.py" folder "{"tempdir}/DeployOpts.py" {hasmkb}'
options["hasmkb"]=ur'nomkb'
options["helpfile"]=ur'../docs/Deployment.chm'
options["helppage"]=ur'0'
options["lastdir"]=ur'/Users/danielshir/Work/InnoBell/Mooniz/Box2dTest/build_box2dtest_xcode'
options["mkb"]=ur'/Developer/Marmalade/5.2/extensions/s3eNextpeer/s3eNextpeerTest/test1.mkb'
options["mkbdir"]=ur'/Developer/Marmalade/5.2/extensions/s3eNextpeer/s3eNextpeerTest'
options["mkbfile"]=ur'test1.mkb'
options["outdir"]=ur'/Developer/Marmalade/5.2/extensions/s3eNextpeer/s3eNextpeerTest/build_test1_xcode'
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
t["endDir"]="/Developer/Marmalade/5.2/extensions/s3eNextpeer/s3eNextpeerTest/build_test1_xcode/deployments/default/iphone/release"
