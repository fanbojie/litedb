import glob
import os
from datetime import date

RIGHT_RESERVED = 'SVN-Author'

DESCRIPT='''//
//  $Id$
//
//  Copyright (c)1992-2013, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//    Description:    
//    Revisions:        Year-Month-Day      SVN-Author       Modification
//                        {year}        {author}            Create
//

'''

if __name__ == "__main__":
    authorName = raw_input("please input author name:")
    files = glob.glob('*.h')
    for headfile in files:
        with open(headfile, 'r+') as f:
            hasDiscript = False
            lines = f.readlines()
            for line in lines:
                if RIGHT_RESERVED in line:
                    hasDiscript = True
                    break
            if not hasDiscript:
                now = date.today();
                descript = DESCRIPT.format(year=now, author=authorName)
                f.seek(0, os.SEEK_SET)
                f.write(descript)
                f.writelines(lines)
                    
            
    
    
