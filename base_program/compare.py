def main():
    org_src, org_inc = getLinesMake(getFile('Makefile_org'))
    cmp_src, cmp_inc = getLinesMake(getFile('Makefile_cmp'))

    delta_src = filterLines(org_src, cmp_src)
    delta_inc = filterLines(org_inc, cmp_inc)

    # print('SRC: ')
    # printList(delta_src)
    # print('\n')

    # print('INC: ')
    # printList(delta_inc)
    # print('\n')

    org_sdk = getFile('sdk_config_org.h')
    cmp_sdk = getFile('sdk_config_cmp.h')

    printList(filterLines(org_sdk, cmp_sdk))
    
def filterLines(org, cmp):
    return [l for l in org if l not in cmp]
    
def printList(lst):
    for line in lst:
        print(line)

def getFile(path):
    with open(path, 'r') as file:
        return file.readlines()

def getLinesSdkConfig(file):
    pass

def getLinesMake(file):
    src, inc = [], []
    flag_add_src = False
    flag_add_inc = False

    for line in file:
        if 'SRC_FILES' in line:
            flag_add_src = True
            flag_add_inc = False
        elif 'INC_FOLDERS' in line:
            flag_add_inc = True
            flag_add_src = False
        
        if '+=' in line or '#' in line: continue
        if ('OPT' in line): break

        line = line.replace('\r\n', '')
        line = line.replace('  ', '')

        if line == '': continue

        if flag_add_src:
            src.append(line)
        elif flag_add_inc:
            inc.append(line)
        
    return src, inc
        

if __name__ == '__main__':
    main()


