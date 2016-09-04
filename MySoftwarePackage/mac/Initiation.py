import ROOT , sys , os , time
ROOT.gStyle.SetOptStat(0000)

def dirname( ):
    dirfmt = "/Users/erezcohen/Desktop/%4d-%02d-%02d"
    dirname = dirfmt % time.localtime()[0:3]
    return dirname;

def createnewdir( ):
    dirfmt = "/Users/erezcohen/Desktop/%4d-%02d-%02d"
    dirname = dirfmt % time.localtime()[0:3]
    try:
        os.makedirs(dirname)
    except OSError, e:
        if e.errno != 17:
            raise # This was not a "directory exist" error..
        return

def create_dir( path , dir_name ):
    dirname = path + "/" + dir_name
    try:
        os.makedirs( dirname )
    except OSError, e:
        if e.errno != 17:
            raise # This was not a "directory exist" error..
        return

