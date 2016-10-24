import ROOT , sys , os , time
ROOT.gStyle.SetOptStat(0000)

def generate_directory(dirname):
    try:
        os.makedirs(dirname)
    except OSError, e:
        if e.errno != 17:
            raise # This was not a "directory exist" error..
        return


def createnewdir():
    dirfmt = "/Users/erezcohen/Desktop/%4d-%02d-%02d"
    dirname = dirfmt % time.localtime()[0:3]
    return dirname


def create_dated_dir( name ):
    time = "%4d-%02d-%02d"
    time_name = time % time.localtime()[0:3]
    dirfmt = "/Users/erezcohen/Desktop/%s-%s"%(name,time_name)
    generate_directory(dirname)
    return dirname


def create_dir( path , dir_name ):
    generate_directory(dirname)
    return dirname

