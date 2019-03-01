// This program is a part of NT MudLIB

#define FIRST_PRELOAD   "/adm/daemons/systemd.c"


// Function name:   update_file
// Description:     reads in a file, ignoring lines that begin with '#'
// Arguements:      file: a string that shows what file to read in.
// Return:          Array of nonblank lines that don't begin with '#'
// Note:            must be declared static (else a security hole)
protected string *update_file(string file)
{
        string *list;
        string str;
        int i;

        str = read_file(file);
        if( !str )
                return ({});

        list = explode(str, "\n");
        for (i = 0; i < sizeof(list); i++)
                if( list[i][0] == '#')
                        list[i] = 0;

        list -= ({ 0 });
        return list;
}

// Function name:       epilog
// Return:              List of files to preload
// 初始化作業 Initialization
// 若 driver 參數為 -e , flag 為非零值

string *epilog(int flag)
{
        /*
        string *items;

        items = update_file(CONFIG_DIR + "preload");
        return items;
        */

        if( flag )
        {
                printf("驅動程式取消預先載入程序。\n");
                log_file("preload/preload","驅動程式取消預先載入程序。\n");
                return allocate(0);
        }

        return ({ FIRST_PRELOAD });
}

// preload an object
// 預先載入物件
void preload(string file)
{
        mixed err;

        if( objectp(find_object(file)) )
                return;

        if( err = catch(load_object(file)) )
                log_file("static/preload",sprintf("載入 %s 時發生錯誤: %O\n", file, err));
}
