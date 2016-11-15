import os

# prints
def print_line():
    print '\033[92m' + '--------------------------------------------------------------' + '\033[0m'

def print_important(string):
    print '\033[94m' + '\033[1m' + string + '\033[0m' ; print_line

def print_filename(filename,action_on_file=""):
    print action_on_file + '\n' + '\033[91m' + filename + '\033[0m'



# ------------------------------------------------------------------------------- #
def stream_dataframe_to_file( df , filename ):
    # if file does not exist write header
    if not os.path.isfile(filename):
        df.to_csv(filename,header ='column_names' , index = False)
    else: # else it exists so append without writing the header
        df.to_csv(filename,mode = 'a', header=False , index = False)

