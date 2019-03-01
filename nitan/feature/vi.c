/* Program      : /feature/me.c 
 * Author       :Kenny@Eternal.Civilization (3/25/1998) 
 * 
 * port to chinese wizard group : /feature/vi.c by ken@chinesemud.net (99-3-15) 
 */ 
 
#include <ansi.h>                       // 定義 ANSI/VT100 終端機的逸脱碼 
 
#define ECHO 0                          // 讀取輸入時要顯示字元 
#define HIDE 1                          // 讀取輸入時不顯示字元 
#define REFRESH 1                       // 讀取輸入後要重繪畫面 
#define LOGFILE "static/VI"             // 檔案異動記錄檔 
 
void start_edit(string filename);       // 呼叫編輯器，開始編輯 
private void _append(object pl);        // 在遊標後面加字 
private void _append_line(object pl);   // 在遊標底下加一新行 
private void _backspace(object pl);     // 刪除遊標前的字 
protected void _confirm_save(string str, object pl); // 離開編輯器前確認存檔 
private void _del_char(object pl, int bs);      // 刪除遊標上的字 
private void _del_line(object pl);              // 刪除整行 
private int  _dispatcher(object pl);            // 分派指令到不同函式 
private void _down(object pl);                  // 遊標往下移一行 
private void _end(object pl);                   // 將遊標移到行尾 
private void _esc(object pl);                   // 從輸入模式回到命令模式 
private void _file_end(object pl);              // 將遊標移到檔尾 
private void _file_head(object pl);             // 將遊標移到檔頭 
private void _goto_line(object pl);             // 跳到特定行去 
protected void _goto_line_done(string str, object pl, int rein); // 取得行號 
private void _help(object pl);                  // 輔助畫面 
private void _home(object pl);                  // 將遊標移到行首 
protected void _input(string str, object pl, int fresh); // 讀得輸入字串 
private void _insert(object pl);                // 在遊標前面插字 
private void _insert_line(object pl);           // 在遊標上方加一新行 
private void _insert_exclam_mark(object pl);    // 在遊標前面插入一個「!」字元 
private void _join(object pl);                  // 將下行文字移到此行後面 
private void _keymap(object pl);                // 定義新功能鍵 
protected void _keymap_done(string str, object pl); // 取得定義功能鍵 
private void _left(object pl);                  // 遊標往左移一字 
// 在狀態列顯示訊息 
private varargs void _message(object pl, string str, string callback, int hide, 
mixed arg); 
protected void _message_done(string str, object pl); // 結束訊息的顯示 
private void _next_match(object pl);            // 搜尋/替換下個符合字串 
private void _page_down(object pl);             // 往下卷一頁（22 行） 
private void _page_up(object pl);               // 往上卷一頁（22 行） 
private void _process(object pl);               // 處理輸入模式的字串輸入 
protected void _quit(mixed unused, mixed pl);   // 離開編輯器 
private void _refresh(object pl);               // 更新畫面 
private void _refresh_cursor(object pl);        // 更新遊標位置 
// 重繪畫面 
private void _refresh_screen(object pl, int s_row, int e_row, int s_col); 
private void _refresh_status(object pl);        // 更新狀態列 
private void _replace(object pl);               // 字串替換 
protected void _replace_done(string str, object pl); // 取得替換字串 
private void _right(object pl, int col, int extra);  // 遊標往右移一字 
private void _search(object pl);                     // 字串搜尋 
protected void _search_done(string str, object pl);  // 取得搜尋字串 
private void _tab(object pl);                        // 命令模式下 TAB 鍵的定位 
private void _undef_key(object pl);                  // 取消某功能鍵定義 
protected void _undef_key_done(string str, object pl); // 取得指定功能鍵 
private void _up(object pl);                           // 遊標往上移一行 
private void _write(object pl);                        // 取得儲存檔案名稱 
protected void _write_done(string str, object pl, int quit); // 儲存檔案 
 
private mapping EditedFiles=([ ]);              // 編輯中的檔案 
/* 
int iS_Row, iE_Row,                             // 可見視窗的始末行號 
    iS_Col, iE_Col,                             // 可見視窗的始未欄位 
    iRow,   iCol,                               // 遊標位置 
    is_Command_Mode, is_NewFile, is_Modify,     // 檔案狀況旗標 
    is_Substituted;                             // 代換內碼旗標 
string *sText,                                  // 檔案內容 
       sChar, sOldChar,                         // 輸入字串（命令） 
       sCount,                                  // 命令計數 
       sFileName,                               // 編輯檔名 
       sSearch, sReplace;                       // 搜尋/替換字串 
mapping keymap;                                 // 功能鍵定義對照表 
*/ 
 
void start_edit(string file)                // 呼叫編輯器，開始編輯 
{ 
        int  i; 
        mapping me; 
 
 
        if (objectp(EditedFiles[file])) 
        { 
                write(sprintf("%s 正在編輯這個檔案，請稍候再編輯。\n", 
                        capitalize(EditedFiles[file]->query("id")))); 
                return; 
        } // if 
        this_player()->set_temp("me", ([ ])); 
        me = this_player()->query_temp("me"); 
        me["sFileName"] = file; 
        if (file_size(file) <= 0) 
        {        // 檔案長度小於 1 
                me["sText"] = ({ "" }); 
                if (file_size(file) < 0) 
                {        // 新檔 
                        me["is_Command_Mode"] = 0; 
                        me["is_NewFile"] = 1; 
                } 
        } 
        else 
        { 
                string content=read_file(file), tabs="        "; 
 
                // 檔案長度大於 0 
                me["is_Command_Mode"] = 1; 
                me["is_NewFile"] = 0; 
                if (stringp(content)) 
                { 
                        me["sText"] = explode(read_file(file), "\n"); 
                        // 將 TAB，以 8 個空白代替，以方便遊標位置的計算 
                        for (i=sizeof(me["sText"])-1; i>=0; i--) 
                        { 
                                int len=sizeof(me["sText"][i]); 
                                reset_eval_cost(); 
                                for (int j=0; j<len; j++) 
                                        if (me["sText"][i][j] == '\t') 
                                                me["sText"][i] = replace_string( 
                                                        me["sText"][i], "\t", tabs[0..7-j%8]); 
                        } 
                } 
                else me["sText"] = ({ "" }); 
        } // old file 
 
        me["sCount"] = ""; 
        me["sSearch"] = me["sReplace"] = me["is_Modify"] = 0; 
        me["iE_Row"] = 23; 
        me["iS_Row"] = me["iS_Col"] = me["iRow"] = me["iCol"] = 1; 
        EditedFiles += ([ file: this_player()->link() ]); 
 
        // 取得/設定功能鍵定義對照表 
             if (!mapp(me["keymap"] = this_player()->query("me_keymap"))) 
                     me["keymap"] = ([ ]); 
        if (this_player()->query("me_no_help") || 
            this_player()->query_temp("no_me_help")) 
        {        // 非第一次使用編輯器，直接進入編輯器 
                _refresh_screen(this_player(), 1, 23, 1); 
 
                get_char("_input", HIDE, this_player()); 
        } 
        else 
        {        // 第一次使用編輯器，先看功能説明 
                this_player()->set_temp("no_me_help", 1); 
                _help(this_player()); 
        } 
} // start_edit() 
 
 
private void _refresh_cursor(object pl)        // 更新遊標位置 
{ 
        mapping me=pl->query_temp("me"); 
        printf(ESC "[%d;%df", me["iRow"]+1, me["iCol"]); 
} // _refresh_cursor() 
 
 
private void _refresh_status(object pl)        // 更新狀態列 
{ 
        mapping me=pl->query_temp("me"); 
 
        // 移動遊標到 (1,1)，用反相字元顯示狀態列 
        printf(HOME + NOR + REV + "列:%4d 行:%3d %-43s %10s [命令模式]" + NOR, 
                me["iS_Row"]+me["iRow"]-1, me["iS_Col"]+me["iCol"]-1, 
                sprintf("%s %s", me["sFileName"], (me["is_Modify"]? "(已修改)": 
                (me["is_NewFile"]? "(新檔)": "")))[0..42], 
                (me["is_Command_Mode"]? "?:輔助畫面": "[輸入模式]")); 
        _refresh_cursor(pl); 
} // _refresh_status() 
 
 
// 重繪畫面 
private void _refresh_screen(object pl, int s_row, int e_row, int s_col) 
{ 
        int  i, temp; 
        mapping me=pl->query_temp("me"); 
 
 
        if (e_row < s_row)                // 檢查始末行號的先後次序 
        { 
                temp = e_row; 
                e_row = s_row; 
                s_row = temp; 
        } 
 
        if (s_row < 1) s_row = 1; 
        if (s_col < 1) s_col = 1; 
        if (e_row > sizeof(me["sText"])) // 不能超過檔尾 
                e_row = sizeof(me["sText"]); 
        if (e_row-s_row > 22) e_row = s_row+22; 
 
        me["iS_Row"] = s_row;        me["iE_Row"] = e_row; 
        me["iS_Col"] = s_col;        me["iE_Col"] = s_col+79; 
 
        printf(REF+NOR);                // 清除畫面，移動遊標到 (1,1) 
        for (i=me["iS_Row"]-1; i<me["iE_Row"]; i++) 
                printf("\r\n%s", me["sText"][i][me["iS_Col"]-1..me["iE_Col"]-1]); 
        for (i=me["iS_Row"]+22-me["iE_Row"]; i>0; i--) 
                printf("\r\n~");        // 不足行號用 ~ 表示 
        _refresh_status(pl); 
} // _refresh_screen() 
 
 
protected void _input(string str, object pl, int fresh) // 讀得輸入字串 
{ 
        int    i, size, bs=0; 
        string *chars; 
        mapping me=pl->query_temp("me"); 
 
        if (fresh) 
        {        // 重繪畫面 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
                get_char("_input", HIDE, pl); 
                return; 
        } 
 
        me["is_Substituted"] = 1;       // 先設定代換內碼旗標 
        if (str == "")                  // 代換掉 Backspace/Ctrl-Backspace 
        { 
                str = "BACKSPACE"; 
                bs = 1; 
        } 
        if (str[0] == 27) 
        { 
                chars = explode(str, ESC);      // 逸脱碼的字串，以 ESC 斷開 
                for (i=sizeof(chars)-1; i>=0; i--) 
                        chars[i] = ESC + chars[i];      // 加回 ESC 
                if (sizeof(chars) == 0)                 // 若只是單一字元 ESC 
                        chars = ({ ESC }); 
        } 
        else    chars = ({ str }); 
 
        size = sizeof(chars); 
        for (i=0; i<size; i++) 
        {        // 轉換逸脱碼為編輯器內碼 
                switch (chars[i]) 
                { 
                case "\t":       me["sChar"] = "TAB";   break; 
                case "\r":       me["sChar"] = "ENTER"; break; 
                case ESC:        me["sChar"] = "ESC";   break; 
                case ESC "OA": 
                case ESC "[A":   me["sChar"] = "UP";    break; 
                case ESC "OB": 
                case ESC "[B":   me["sChar"] = "DOWN";  break; 
                case ESC "OC": 
                case ESC "[C":   me["sChar"] = "RIGHT"; break; 
                case ESC "OD": 
                case ESC "[D":   me["sChar"] = "LEFT";  break; 
                case ESC "OH": 
                case ESC "[H": 
                case ESC "1~": 
                case ESC "[1~":  me["sChar"] = "HOME";  break; 
                case ESC "[2~":  me["sChar"] = "INSERT";break; 
                case ESC "[3~":  me["sChar"] = "DELETE";break; 
                case ESC "4~":   me["sChar"] = "END";   break; 
                case ESC "[4~":  me["sChar"] = "END";   break; 
                case ESC "[5~":  me["sChar"] = "PAGEUP";break; 
                case ESC "[6~":  me["sChar"] = "PAGEDOWN";break; 
                case ESC "OP":   me["sChar"] = "F1";    break; 
                case ESC "OQ":   me["sChar"] = "F2";    break; 
                case ESC "OR":   me["sChar"] = "F3";    break; 
                case ESC "OS":   me["sChar"] = "F4";    break; 
                case ESC "m":    me["sChar"] = "F5";    break; 
                case ESC "[17~": me["sChar"] = "F6";    break; 
                case ESC "[18~": me["sChar"] = "F7";    break; 
                case ESC "[19~": me["sChar"] = "F8";    break; 
                case ESC "[20~": me["sChar"] = "F9";    break; 
                case ESC "[21~": me["sChar"] = "F10";   break; 
                case ESC "[23~": me["sChar"] = "F11";   break; 
                case ESC "[24~": me["sChar"] = "F12";   break; 
                default: 
                        if (sizeof(chars[i])==1 && 
                            0<chars[i][0] && chars[i][0]<27) 
                                switch (chars[i][0]) 
                                { // 代換內碼，使在輸入模式也能使用指令 
                                case  1: me["sChar"]="Ctrl-A"; break; 
                                case  2: me["sChar"]="Ctrl-B"; break; 
                                case  4: me["sChar"]="Ctrl-D"; break; 
                                case  6: me["sChar"]="Ctrl-F"; break; 
                                case  7: me["sChar"]="Ctrl-G"; break; 
                                case 10: me["sChar"]="Ctrl-J"; break; 
                                case 11: me["sChar"]="Ctrl-K"; break; 
                                case 12: me["sChar"]="Ctrl-L"; break; 
                                case 14: me["sChar"]="Ctrl-N"; break; 
                                case 15: me["sChar"]="Ctrl-O"; break; 
                                case 16: me["sChar"]="Ctrl-P"; break; 
                                case 17: me["sChar"]="Ctrl-Q"; break; 
                                case 18: me["sChar"]="Ctrl-R"; break; 
                                case 19: me["sChar"]="Ctrl-S"; break; 
                                case 20: me["sChar"]="Ctrl-T"; break; 
                                case 21: me["sChar"]="Ctrl-U"; break; 
                                case 22: me["sChar"]="Ctrl-V"; break; 
                                case 23: me["sChar"]="Ctrl-W"; break; 
                                case 24: me["sChar"]="Ctrl-X"; break; 
                                case 25: me["sChar"]="Ctrl-Y"; break; 
                                case 26: me["sChar"]="Ctrl-Z"; break; 
                        } // switch 
                        else 
                        { 
                                me["sChar"] = chars[i];            // 此為普通字串 
                                if (!bs) me["is_Substituted"] = 0; // 清除代換內 
                        } // else 
                } // switch 
                // 將轉換後的字串送到分派指令函式處理，並等待讀取下個輸入 
                if (_dispatcher(pl) && i==size-1) get_char("_input", HIDE, pl); 
        } // for 
} // input() 
 
 
private int _dispatcher(object pl)                // 分派指令到不同函式 
{ 
        int  i, count=1; 
        mapping me=pl->query_temp("me"); 
 
 
        if ( me["is_Command_Mode"] || 
            (me["is_Substituted"] && // 讓輸入模式也能使用某些指令 
             // 這二個指令不在這處理 
             me["sChar"]!="ENTER" && me["sChar"]!="TAB") ) 
        {        // 現在是命令模式 
                if (sizeof(me["sChar"])!=1 && !me["is_Substituted"]) 
                        return 1; 
                // 檢查功能鍵定義對照表，重新定義命令 
                if (!undefinedp(me["keymap"][me["sChar"]])) 
                        me["sChar"] = 
                        me["keymap"][me["sChar"]]; 
                if (!stringp(me["sChar"])) return 1; // Type checking... 
                // 檢查是數字的話，就是附加到命令計數裏 
                if ('0'<=me["sChar"][0] && me["sChar"][0]<='9') 
                        me["sCount"] += me["sChar"]; 
                else 
                { 
                        sscanf(me["sCount"], "%d", count); 
                        me["sCount"] = ""; // 計數器歸零 
                        // 重覆上個指令 
                        if (me["sChar"] == ".") 
                                me["sChar"] = me["sOldChar"]; 
                        else        // 記錄這次的指令 
                                me["sOldChar"] = me["sChar"]; 
                } 
 
                for (i=0; i<count; i++) 
                        switch (me["sChar"]) // 分派指令到不同函式 
                        { 
                        case "a":_append(pl);                           break; 
                        case "d": 
                        case "Ctrl-D": _del_line(pl);                  break; 
                        case "f": 
                        case "Ctrl-Z": _refresh(pl);                break; 
                        case "g": 
                        case "Ctrl-G": _goto_line(pl);                break; 
                        case "h": 
                        case "LEFT": 
                        case "Ctrl-J": _left(pl);                   break; 
                        case "i":      _insert(pl);                break; 
                        case "j": 
                        case "DOWN": 
                        case "Ctrl-K": _down(pl);                break; 
                        case "k": 
                        case "UP": 
                        case "Ctrl-O": _up(pl);                        break; 
                        case "l": 
                        case "RIGHT": 
                        case "Ctrl-L": _right(pl, 1, 
                                                (me["is_Command_Mode"]?0:1)); 
                                       break; 
                        case "m": _keymap(pl);                        break; 
                        case "n": 
                        case "Ctrl-N": _next_match(pl);                break; 
                        case "o": _append_line(pl);                    break; 
                        case "q":        // 表示不再讀取新輸入，結束編輯 
                        case "F4": 
                        case "Ctrl-Q": _quit(0, pl);                return 0; 
                        case "r": 
                        case "Ctrl-R": _replace(pl);                break; 
                        case "s": 
                        case "Ctrl-S": _search(pl);                   break; 
                        case "u": _undef_key(pl);                break; 
                        case "w": 
                        case "F2": 
                        case "Ctrl-W": _write(pl);                      break; 
                        case "x": 
                        case "DELETE": 
                        case "Ctrl-X":   _del_char(pl, 0);        break; 
                        case "A": 
                        case "HOME": 
                        case "Ctrl-A":   _home(pl);        break; 
                        case "B": 
                        case "PAGEUP": 
                        case "Ctrl-B":   _page_up(pl);        break; 
                        case "E": 
                        case "END": 
                        case "Ctrl-E":   _end(pl);        break; 
                        case "F": 
                        case "PAGEDOWN": 
                        case "Ctrl-F":   _page_down(pl);        break; 
                        case "J": 
                        case "Ctrl-P": _join(pl);         break; 
                        case "O": _insert_line(pl);         break; 
                        case "U": 
                        case "Ctrl-U": _file_head(pl);        break; 
                        case "V": 
                        case "Ctrl-V": _file_end(pl);        break; 
                        case "?": 
                        case "F1": 
                        case "Ctrl-Y": _help(pl);         break; 
                        case "~": 
                        case "Ctrl-T": _insert_exclam_mark(pl);        break; 
                        case "BACKSPACE": _backspace(pl);          break; 
                        case "ESC": _esc(pl);                         break; 
                        case "TAB": _tab(pl);                        break; 
                        } // switch 
        } // if me["is_Command_Mode"] 
        else 
                _process(pl);                // 處理輸入模式的字串輸入 
 
        return 1;                        // 表示繼續讀取新輸入，繼續編輯 
} // dispatcher() 
 
 
private void _append(object pl)                // 在遊標後面加字 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (sizeof(me["sText"]) == 0) return; 
        me["is_Command_Mode"] = 0; 
        _refresh_status(pl); 
        _right(pl, 1, 1); 
} // _append() 
 
 
private void _append_line(object pl)        // 在遊標底下加一新行 
{ 
        string *text; 
        mapping me=pl->query_temp("me"); 
 
        me["is_Command_Mode"] = me["is_NewFile"] = 0; 
        me["is_Modify"] = 1; 
        text = me["sText"][0..me["iS_Row"]+me["iRow"]-2] + ({ "" }) + 
                me["sText"][me["iS_Row"]+me["iRow"]-1..<1]; 
        me["sText"] = text; 
        _refresh_screen(pl, me["iS_Row"], sizeof(me["sText"]), 1); 
        me["iCol"] = 1; 
        _down(pl); 
} // _append_line() 
 
 
private void _backspace(object pl)        // 刪除遊標前的字 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (me["iS_Col"] == me["iCol"])        return; 
        _left(pl); 
        _del_char(pl, 1); 
} // _backspace() 
 
 
protected void _confirm_save(string str, object pl) // 離開編輯器前確認存檔 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (str=="y" || str=="Y") return _write_done("", pl, 1); 
        me["is_Modify"] = 0;                // 設定「未修改」旗標 
        _quit(0, pl); 
} // _confirm_save() 
 
 
private void _del_char(object pl, int bs)                // 刪除遊標上的字 
{ 
        int    go_left=0;                // 是否在刪除後要左移遊標 
        string str; 
        mapping me=pl->query_temp("me"); 
 
 
        if (sizeof(me["sText"])==0 || 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])==0) 
             return; 
        if (me["is_NewFile"] || !me["is_Modify"]) 
        { 
                me["is_NewFile"] = 0; 
                me["is_Modify"] = 1; 
                _refresh_status(pl); 
        } 
 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2]); 
                return; 
        str = me["sText"][me["iS_Row"]+me["iRow"]-2][0..me["iS_Col"]+me["iCol"]-3]; 
        // 檢查是否需要附加剩下的內容 
        if (me["iS_Col"]+me["iCol"]-1 < 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])) 
                str += me["sText"][me["iS_Row"]+ 
                me["iRow"]-2][me["iS_Col"]+me["iCol"]-1..<1]; 
        else        go_left = 1;                // 因為是刪除行尾的字，所以要左  
        me["sText"][me["iS_Row"]+me["iRow"]-2] = str; 
        printf(ESC "[%d;1f%-80s", me["iRow"]+1,        me["sText"][me["iS_Row"]+ 
                me["iRow"]-2][me["iS_Col"]-1..me["iE_Col"]-1]); 
        if (go_left && !bs) _left(pl); 
        else        _refresh_cursor(pl); 
} // _del_char() 
 
 
private void _del_line(object pl)        // 刪除整行 
{ 
        string *text=({ }); 
        mapping me=pl->query_temp("me"); 
        me["is_NewFile"] = 0; 
        me["is_Modify"] = 1; 
        if (me["iS_Row"]+me["iRow"]-2 > 0) 
                text = me["sText"][0..me["iS_Row"]+me["iRow"]-3]; 
        text += me["sText"][me["iS_Row"]+me["iRow"]-1..<1]; 
        me["sText"] = text; 
        _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
        if (me["iS_Row"]+me["iRow"]-1 > sizeof(me["sText"])) 
                _up(pl);                // 若是刪除最後一行，就要上移遊標 
        // 若遊標的新位置超過行尾，則移動遊標到行尾 
        else if (me["iS_Col"]+me["iCol"]-1 > 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])) 
            _end(pl); 
} // _del_line() 
 
 
private void _down(object pl)                // 遊標往下移一行 
{ 
        int  acc; 
        mapping me=pl->query_temp("me"); 
 
 
        // 檢查是否已在檔尾 
        if (me["iS_Row"]+me["iRow"]-1 >= sizeof(me["sText"])) 
                // 若已顯示檔尾下一行，則不做事 
                if (me["iRow"] < 23) return; 
                else 
                {        // 多顯視檔尾下一行，以突顯檔尾的存在 
                        me["iS_Row"]++; 
                        printf(ESC "[24;1f\r\n~"); 
                        me["iRow"] = 22; 
                } 
        else if (++me["iRow"] > 23) 
        {        // 畫面上卷，顯示下一行 
                me["iS_Row"]++;                me["iE_Row"]++; 
                printf(ESC "[24;1f\r\n%s", me["sText"][me["iE_Row"]-1] 
                        [me["iS_Col"]-1..me["iE_Col"]-1]); 
                me["iRow"] = 23; 
        } 
 
        // 若遊標的新位置超過行尾，則移動遊標到行尾 
        if (me["iS_Col"]+me["iCol"]-1 > 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])) 
                me["iCol"] = sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])- 
                        me["iS_Col"]+(me["is_Command_Mode"]?1:2); 
        // 若此行無字，則定位在第一欄 
        if (me["iCol"]==0 && me["iS_Col"]==1) me["iCol"] = 1; 
        if (me["iCol"] > 0)_refresh_status(pl); 
        else 
        {        // 遊標的新位置在原畫面外，需要重繪畫面 
                acc = me["iCol"];        me["iCol"] = 1; 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], 
                        me["iS_Col"]+acc-1); 
        } 
} // _down() 
 
 
private void _end(object pl)                // 將遊標移到行尾 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (sizeof(me["sText"]) == 0) return; 
        // 計算行尾的位置 
        me["iCol"] = sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])- 
                me["iS_Col"]+(me["is_Command_Mode"]?1:2); 
        if (me["iCol"] == 0) me["iCol"] = 1; // 若此行無字，則定位在第一欄 
        if (sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2]) < me["iE_Col"]) 
                    _refresh_status(pl); 
        else 
        {        // 遊標的新位置在原畫面外，需要重繪畫面 
                me["iCol"] = 79; 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]+ 
                        (sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])- 
                        me["iE_Col"]+1)); 
        } 
} // _end() 
 
 
private void _esc(object pl)                // 從輸入模式回到命令模式 
{ 
        mapping me=pl->query_temp("me"); 
        me["is_Command_Mode"] = 1; 
        _left(pl); 
} // _esc() 
 
 
private void _file_end(object pl)        // 將遊標移到檔尾 
{ 
        mapping me=pl->query_temp("me"); 
        if (sizeof(me["sText"]) == 0) return; 
        _goto_line_done(sprintf("%d", sizeof(me["sText"])), pl, 0); 
} // _file_end() 
 
 
private void _file_head(object pl)        // 將遊標移到檔頭 
{ 
        mapping me=pl->query_temp("me"); 
        if (sizeof(me["sText"]) == 0) return; 
        _goto_line_done("1", pl, 0); 
} // _file_head() 
 
 
private void _goto_line(object pl)        // 跳到特定行去 
{ 
        mapping me=pl->query_temp("me"); 
        _message(pl, sprintf("請輸入行號（直接按 ENTER 取消，1~%d)：", 
                sizeof(me["sText"])), "_goto_line_done", ECHO, 1); 
} // _goto_line() 
 
 
protected void _goto_line_done(string str, object pl, int rein) // 取得行號 
{ 
        int        no; 
        mapping me=pl->query_temp("me"); 
 
        if (str == "") return _message_done("", pl); 
        if (sscanf(str, "%d", no)!=1 || no<1 || no>sizeof(me["sText"])) 
                return _message(pl, "錯誤的行號！", "_message_done", HIDE); 
 
        me["iCol"] = 1; 
        if (me["iS_Row"]<=no && no<=me["iE_Row"]) 
        {        // 指定行號在原可視範圍中 
                me["iRow"] = no-me["iS_Row"]+1; 
                _refresh_status(pl); 
        } 
        else 
        {        // 指定行號不在原可視範圍中，需要重繪畫面 
                me["iS_Row"] = no-11; 
                if (me["iS_Row"] < 1)        me["iS_Row"] = 1; 
                if (me["iE_Row"] < no+11)        me["iE_Row"] = no+11; 
                me["iRow"] = no-me["iS_Row"]+1; 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], 1); 
        } 
        if (rein) get_char("_input", HIDE, pl); // 檢查是否需要讀取下次輸入 
} // _goto_line_done() 
 
 
private void _help(object pl)                // 輔助畫面 
{ 
        printf(REF + 
"         【 LPMud 全螢幕編輯器 】1.3 版 3/25/1998   版權所有.\r 
\r 
 a            在遊標後面加字          d  Ctrl-D    刪除整行\r 
 f  Ctrl-Z    更新畫面                g  Ctrl-G    跳到特定行去\r 
 h  Ctrl-J    遊標往左移一字          i            在遊標前面插字\r 
 j  Ctrl-K    遊標往下移一行          k  Ctrl-O    遊標往上移一行\r 
 l  Ctrl-L    遊標往右移一字          m            定義新功能鍵\r 
 n  Ctrl-N    搜尋/替換下個符合字串   o            在遊標底下加一新行\r 
 q  Ctrl-Q    離開編輯器              r  Ctrl-R    字串替換\r 
 s  Ctrl-S    字串搜尋                u            取消某功能鍵定義\r 
 w  Ctrl-W    儲存檔案                x  Ctrl-X    刪除遊標上的字\r 
 A  Ctrl-A    將遊標移到行首          B  Ctrl-B    往上卷一頁（22 行）\r 
 E  Ctrl-E    將遊標移到行尾          F  Ctrl-F    往下卷一頁（22 行）\r 
 J  Ctrl-P    將下行文字接到此行後面  O            在遊標上方加一新行\r 
 U  Ctrl-U    將遊標移到檔頭          V  Ctrl-V    將遊標移到檔尾\r\n"); 
        printf( 
" .            重覆上個指令            ?  Ctrl-Y    輔助畫面（此畫面）\r 
 ~   Ctrl-T    在遊標前面插入一個「!」字元\r\n 
 合法的定義鍵是字母和 ESC、F1～F12、BACKSPACE、TAB、ENTER、INSERT、DELETE、\r 
 HOME、END、PAGEUP、PAGEDOWN、UP、DOWN、LEFT、RIGHT、Ctrl-A～Ctrl-Z。\r 
\r 
 歡迎傳播此編輯器，但請保留版權宣告，有任何問題和建議請聯絡我：\r 
 kenny@cindy.cis.nctu.edu.tw。\r 
                                                  [按任意鍵回到編輯器]" 
); 
        get_char("_input", HIDE, pl, REFRESH); // 讀取按鍵以重繪畫面 
} // _help() 
 
 
private void _home(object pl)                // 將遊標移到行首 
{ 
        mapping me=pl->query_temp("me"); 
 
        me["iCol"] = 1; 
        if (me["iS_Col"] == 1)_refresh_status(pl); 
        else        _refresh_screen(pl, me["iS_Row"], me["iE_Row"], 1); 
} // _home() 
 
 
private void _insert(object pl)                // 在遊標前面插字 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (sizeof(me["sText"]) == 0) return; 
        me["is_Command_Mode"] = 0; 
        _refresh_status(pl); 
} // _insert() 
 
 
private void _insert_line(object pl)        // 在遊標上方加一新行 
{ 
        string *text=({ }); 
        mapping me=pl->query_temp("me"); 
 
        me["is_Command_Mode"] = me["is_NewFile"] = 0; 
        me["is_Modify"] = 1; 
        // 檢查是否遊標上方是否有內容 
        if (me["iS_Row"]+me["iRow"]-3 >= 0) 
                text = me["sText"][0..me["iS_Row"]+me["iRow"]-3]; 
        text += ({ "" }); 
        text += me["sText"][me["iS_Row"]+me["iRow"]-2..<1]; 
        me["sText"] = text; 
        me["iCol"] = 1; 
        _refresh_screen(pl, me["iS_Row"], sizeof(me["sText"]), 1); 
} // _insert_line() 
 
 
private void _insert_exclam_mark(object pl) // 在遊標前面插入一個「!」字元 
{ 
        mapping me=pl->query_temp("me"); 
 
        // 因為無法正常輸入「!」，所以特地加此函式以輸入「!」。 
        if (sizeof(me["sText"]) == 0) return; 
        me["sChar"] = "!"; 
        _process(pl); 
} // _insert_!() 
 
 
private void _join(object pl)                // 將下行文字移到此行後面 
{ 
        string *text=({ }); 
        mapping me=pl->query_temp("me"); 
 
 
        if (me["iS_Row"]+me["iRow"]-1 >= sizeof(me["sText"])) return; 
 
        me["is_NewFile"] = 0; 
        me["is_Modify"] = 1; 
        _end(pl);                        // 先將遊標移到行尾 
        text = me["sText"][0..me["iS_Row"]+me["iRow"]-2]; 
        if (sizeof(me["sText"][me["iS_Row"]+me["iRow"]-1])) 
        {        // 若下行有內容附加上來 
                text[me["iS_Row"]+me["iRow"]-2] += (" "+ 
                        me["sText"][me["iS_Row"]+me["iRow"]-1]); 
                _right(pl, 1, 1); 
        } 
        text += me["sText"][me["iS_Row"]+me["iRow"]..<1]; 
        me["sText"] = text; 
        _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
} // _join() 
 
 
private void _keymap(object pl)                // 定義新功能鍵 
{ 
        _message(pl, "請輸入新定義鍵和原功\能鍵（直接按 ENTER 取消，以空白隔開）", 
                "_keymap_done", ECHO); 
} // _keymap() 
 
 
protected void _keymap_done(string str, object pl) // 取得定義功能鍵 
{ 
        string old, _new; 
        mapping me=pl->query_temp("me"); 
 
        _refresh_status(pl); 
        if (str != "") 
        {        // 若有資料輸入 
                if (sscanf(str, "%s %s", _new, old) != 2) 
                        return _message(pl, "輸入格式錯誤。", "_message_done", 
                                HIDE); 
                me["keymap"][_new] = old; 
                _message(pl, sprintf("好了，從此以後新定義鍵「%s」就有原功\能鍵? 
?s」的功\能了！", 
                        _new, old), "_message_done", HIDE); 
        } 
        else        get_char("_input", HIDE, pl); // 取消輸入，繼續讀取下個輸入 
} // _keymap_done() 
 
 
private void _left(object pl)                // 遊標往左移一字 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (me["iS_Col"]==1 && me["iCol"]==1) return _refresh_status(pl); 
        if (--me["iCol"] < 1) 
        {        // 遊標的新位置在原畫面外，需要重繪畫面 
                // 若左移 8 欄太多的話，就只左移一欄 
                if (me["iS_Col"]-8 < 1) 
                        me["iCol"] = me["iS_Col"]-1; 
                else        me["iCol"] = 8; // 不然就設定遊標在第 8 欄位置 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], 
                        me["iS_Col"]-me["iCol"]); 
                return; 
        } 
        _refresh_status(pl); 
} // _left() 
 
 
// 在狀態列顯示訊息 
private varargs void _message(object pl, string str, string callback, int hide, 
mixed arg) 
{ 
        printf(HOME + NOR + REV);        // 移動遊標到 (1,1)，設定反相字元顯示 
        // 清除原狀態列的訊息 
        printf(" 
                "); 
        printf(HOME + str);                // 移動遊標到 (1,1)，再顯示訊息 
        input_to(callback, hide, pl, arg); // 讀取輸入資料 
} // _message() 
 
 
protected void _message_done(string str, object pl) // 結束訊息的顯示 
{ 
        _refresh_status(pl); 
        get_char("_input", HIDE, pl);        // 繼續讀取輸入字串 
} // _message_done() 
 
 
private void _next_match(object pl)                // 搜尋/替換下個符合字串 
{ 
        mapping me=pl->query_temp("me"); 
        string str=""; 
        // 設定起始搜尋位置為遊標現在位置 
        int    j=me["iS_Col"]+me["iCol"]-1, 
               i, ofs; 
 
 
        if (!stringp(me["sSearch"])) return; // 若沒先設定搜尋字串，不做事 
 
        for (i=me["iS_Row"]+me["iRow"]-2; i<sizeof(me["sText"]); i++) 
        { 
                if ((ofs = strsrch(me["sText"][i][j-1..<1], me["sSearch"]))== -1) 
                        j = 1; // 這行沒找到的話，設定下行從第一欄開始找 
                else 
                {        // 找到指定字串了, 移動遊標到目的行 
                        _goto_line_done(sprintf("%d", i+1), pl, 0); 
                        me["iCol"] = j+ofs; // 計算指定字串的絕對位置 
                        // 若指定字串落在原畫面外，則重繪畫面 
                        if (me["iCol"]<me["iS_Col"] || 
                            me["iCol"]+strlen(me["sSearch"])>me["iS_Col"]+79) 
                                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], 
                                        me["iCol"]); 
                        if (stringp(me["sReplace"])) 
                        {        // 需要替換字串 
                                me["is_NewFile"] = 0; 
                                me["is_Modify"] = 1; 
                                // 附加遊標前內容 
                                str = me["sText"][i][0..me["iCol"]-2]; 
                                str += me["sReplace"]; 
                                str += (me["sText"][i][me["iCol"]+ 
                                        strlen(me["sSearch"])-1..<1]); 
                                me["sText"][i] = str; 
                                // 若替換字串落在原畫面外，則重繪畫面 
                                if (me["iCol"]<me["iS_Col"] || 
                                    me["iCol"]+strlen(me["sReplace"]) 
                                    > me["iS_Col"]+79) 
                                        _refresh_screen(pl, me["iS_Row"], 
                                                me["iE_Row"], me["iCol"]); 
                                // 將遊漂移到替換字串後面 
                                me["iCol"] = me["iCol"]+strlen(me["sReplace"])- 
                                        me["iS_Col"]+1; 
                                printf(ESC "[%d;1f%-80s", me["iRow"]+1, 
                                        me["sText"][me["iS_Row"]+ 
                                        me["iRow"]-2][me["iS_Col"]-1 
                                        ..me["iE_Col"]-1]); 
                        } 
                        // 將遊漂移到搜尋字串後面 
                        else         
                                me["iCol"] = me["iCol"]+strlen(me["sSearch"])-me["iS_Col"]+1; 
                        _refresh_status(pl); 
                        break; 
                } // if found 
        } // for each row 
        if (i >= sizeof(me["sText"])) 
                _message(pl, "找不到指定字串！", "_message_done", HIDE); 
        else        get_char("_input", HIDE, pl); // 讀取下個輸入字串 
} // _next_match() 
 
 
private void _page_down(object pl)        // 往下卷一頁（22 行） 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (me["iS_Row"]+22 > sizeof(me["sText"])) return; // 檢查是否不能再捲了 
        me["iS_Row"] += 22;        me["iE_Row"] += 22; 
        // 檢查遊標的新位置是否超過檔尾 
        if (me["iS_Row"]+me["iRow"]-1 > sizeof(me["sText"])) 
                me["iRow"] = sizeof(me["sText"])-me["iS_Row"]+1; 
        _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
        // 若遊標的新位置超過行尾，則移動遊標到行尾 
        if (me["iS_Col"]+me["iCol"]-1 > sizeof(me["sText"][me["iS_Row"]+ 
                me["iRow"]-2])) 
                _end(pl); 
} // _page_down() 
 
 
private void _page_up(object pl)        // 往上卷一頁（22 行） 
{ 
        mapping me=pl->query_temp("me"); 
 
        if (me["iS_Row"] <= 1) return; // 檢查是否不能再捲了 
        me["iS_Row"] -= 22; 
        if (me["iS_Row"] < 1) me["iS_Row"] = 1; // 最多隻能翻到第一列 
        _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
        // 若遊標的新位置超過行尾，則移動遊標到行尾 
        if (me["iS_Col"]+me["iCol"]-1 > 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])) 
            _end(pl); 
} // _page_up() 
 
 
private void _process(object pl)        // 處理輸入模式的字串輸入 
{ 
        int    i, size; 
        string str, rest, *input; 
        mapping me=pl->query_temp("me"); 
 
 
        if (me["is_Modify"]==0 || me["is_NewFile"]==1) 
        { 
                me["is_NewFile"] = 0; 
                me["is_Modify"] = 1; 
                _refresh_status(pl); 
        } 
        if (!me["is_Substituted"] && (strsrch(me["sChar"], "\r")!=-1 || 
            strsrch(me["sChar"], "\n")!=-1)) 
                me["is_Substituted"] = 1; // 設定內碼代換旗標 
        me["sChar"] = replace_string(me["sChar"], "\t", "        "); 
        me["sChar"] = replace_string(me["sChar"], "\r", "\rENTER\r"); 
        me["sChar"] = replace_string(me["sChar"], "\n", "\rENTER\r"); 
        input = explode(me["sChar"], "\r"); 
 
        size = sizeof(input); 
        for (i=0; i<size; i++)                // 一次處理一行輸入 
        { 
                if (me["is_Substituted"] && input[i] == "ENTER") 
                {        // 當鍵入 ENTER 時，要將遊標之後的內容移到下面的新行 
                        rest = me["sText"][me["iS_Row"]+ 
                                me["iRow"]-2][me["iS_Col"]+me["iCol"]-2..<1]; 
                        me["sText"][me["iS_Row"]+me["iRow"]-2] = 
                                me["sText"][me["iS_Row"]+ 
                                me["iRow"]-2][0..me["iS_Col"]+me["iCol"]-3]; 
                        _append_line(pl); // 在遊標底下加一新行 
                        // 新行的內容是原遊標位置以後的內容 
                        me["sText"][me["iS_Row"]+me["iRow"]-2] = rest; 
                        continue; 
                } 
 
                // 輸入字串不是 ENTER 時, 處理 TAB 的定位 
                if (me["is_Substituted"] && input[i] == "TAB") 
                        input[i] = "        "[0..7-(me["iCol"]-1)%8]; 
                str = me["sText"][me["iS_Row"]+me["iRow"]-2][0..me["iS_Col"]+ 
                        me["iCol"]-3] + input[i] + me["sText"][me["iS_Row"] + 
                        me["iRow"]-2][me["iS_Col"]+ me["iCol"]-2..<1]; 
                me["sText"][me["iS_Row"]+me["iRow"]-2] = str; 
                _right(pl, sizeof(input[i]), 1); 
        } // for 
 
        printf(ESC "[%d;1f%s", me["iRow"]+1, me["sText"][me["iS_Row"]+ 
                me["iRow"]-2][me["iS_Col"]-1..me["iE_Col"]-1]); 
        _refresh_cursor(pl); 
} // _process() 
 
 
protected void _quit(mixed unused, mixed pl) // 離開編輯器 
{ 
        mapping me; 
 
        seteuid(geteuid(pl)); 
        me = pl->query_temp("me"); 
        if (me["is_Modify"]) 
                return _message(pl, "此檔案已更改，請問需要存檔嗎（y/n)？[n]", 
                        "_confirm_save", ECHO); 
        me["iRow"] = 23; 
        _refresh_cursor(pl);                // 移動遊標到最後一行 
        printf(NOR "\r\n"); 
        // 若功能鍵定義對照表是空的，就清除玩家身上的記錄，不然就記錄在玩家身上 
        if (sizeof(me["keymap"]) == 0) pl->delete("me_keymap"); 
        else pl->set("me_keymap", me["keymap"]); 
        map_delete(EditedFiles, pl->query_temp("me/sFileName")); 
        pl->delete_temp("me"); // 清除編輯器用到的暫時變數 
} // _quit() 
 
 
private void _refresh(object pl)        // 更新畫面 
{ 
        mapping me=pl->query_temp("me"); 
        _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
} // _refresh() 
 
 
private void _replace(object pl)        // 字串替換 
{ 
        _message(pl, "搜尋/替換字串(直接按ENTER取消,以空白隔開):", 
                "_replace_done", ECHO); 
} // _replace() 
 
protected void _replace_done(string str, object pl) // 取得替換字串 
{ 
        mapping me=pl->query_temp("me"); 
 
        _refresh_status(pl); 
        if (str != "") 
        {        // 有輸入資料時 
                if (sscanf(str, "%s %s", me["sSearch"],        me["sReplace"]) != 2) 
                {        // 只有一個字串，就指定為搜尋字串，意即拿掉指定字串 
                        me["sSearch"] = str; 
                        me["sReplace"] = ""; 
                } 
                _next_match(pl); 
        } 
        else        get_char("_input", HIDE, pl); // 繼續讀取下個輸入字串 
} // _replace_done() 
 
 
private void _right(object pl, int col, int extra)        // 遊標往右移一字 
{ 
        int    acc; 
        mapping me=pl->query_temp("me"); 
 
 
        if (sizeof(me["sText"])==0 || me["iS_Col"]+me["iCol"]-1> 
            sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])-1+extra) 
            return; 
        me["iCol"] += col; 
        if (me["iS_Col"]+me["iCol"]-1 > sizeof(me["sText"][me["iS_Row"]+ 
            me["iRow"]-2])+extra) 
                me["iCol"] = sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])- 
                        me["iS_Col"]+1+extra; 
        if (me["iCol"] > 80) 
        {        // 遊標的新位置不在可見視窗內，需要往右移動視窗 
                // 若右移 8 欄太多的話，就只右移到行尾 
                if (me["iE_Col"]+8 > sizeof(me["sText"][me["iS_Row"]+ 
                    me["iRow"]-2])+1) 
                        acc = sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])- 
                                me["iE_Col"]+1; 
                else        acc = 8; 
                me["iCol"] = 80-acc+1;         // 計算遊標的新位置 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]+acc); 
                return; 
        } 
        _refresh_status(pl); 
} // _right() 
 
 
private void _search(object pl)                // 字串搜尋 
{ 
        _message(pl, "請輸入搜尋字串（直接按 ENTER 取消)：", "_search_done", 
                ECHO); 
} // _search() 
 
 
protected void _search_done(string str, object pl) // 取得搜尋字串 
{ 
        mapping me=pl->query_temp("me"); 
 
        _refresh_status(pl); 
        if (str != "") 
        {        // 有輸入資料時 
                me["sSearch"] = str;        me["sReplace"] = 0; 
                _next_match(pl); 
        } 
        else        get_char("_input", HIDE, pl); // 繼續讀取下個輸入字串 
} // _search_done() 
 
 
private void _tab(object pl)                 // 命令模式下 TAB 鍵的定位 
{ 
        mapping me=pl->query_temp("me"); 
        _right(pl, 8-(me["iCol"]-1)%8, 0); 
} // _tab() 
 
 
private void _undef_key(object pl)        // 取消某功能鍵定義 
{ 
        _message(pl, "請輸入欲取消定義之功\能鍵（直接按 ENTER 取消)：", 
                "_undef_key_done", ECHO); 
} // undef_key() 
 
 
protected void _undef_key_done(string str, object pl) // 取得指定功能鍵 
{ 
        mapping me=pl->query_temp("me"); 
        if (str != "")        map_delete(me["keymap"], str); 
        _message_done("", pl); 
} // undef_key_done() 
 
 
private void _up(object pl)                // 遊標往上移一行 
{ 
        int  acc; 
        mapping me=pl->query_temp("me"); 
 
 
        if (me["iRow"]==1 && me["iS_Row"]==1)        return; 
        if (--me["iRow"] < 1) 
        {        // 遊標新位置不在可見視窗內，就上移視窗 
                me["iS_Row"]--; 
                me["iE_Row"]=me["iS_Row"]+22; 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], me["iS_Col"]); 
                me["iRow"] = 1; 
        } 
        // 若遊標新位置超過行尾，則移到行尾 
        if (me["iS_Col"]+me["iCol"]-1 > sizeof(me["sText"][me["iS_Row"]+ 
            me["iRow"]-2])) 
                me["iCol"] = sizeof(me["sText"][me["iS_Row"]+me["iRow"]-2])- 
                        me["iS_Col"]+(me["is_Command_Mode"]?1:2); 
        // 若此行無字，則定位在第一欄 
        if (me["iCol"]==0 && me["iS_Col"]==1) me["iCol"] = 1; 
        if (me["iCol"] > 0) _refresh_status(pl); 
        else 
        {        // 遊標新位置不在可見視窗內，重繪畫面 
                acc = me["iCol"];        me["iCol"] = 1; 
                _refresh_screen(pl, me["iS_Row"], me["iE_Row"], 
                        me["iS_Col"]+acc-1); 
        } 
} // _up() 
 
 
private void _write(object pl)                // 取得儲存檔案名稱 
{ 
        _message(pl, "請輸入新檔名（直接按 ENTER 以使用舊檔名)：", 
                "_write_done", ECHO, 0); 
} // _write() 
 
 
protected void _write_done(string str, object pl, int quit) // 儲存檔案 
{ 
        string callback; 
        mapping me=pl->query_temp("me"); 
 
        if (str == "") str = me["sFileName"]; 
        else        // 取得檔名 
                str = resolve_path(pl->query("cwd"), str); 
        if (quit) callback = "_quit"; 
        else callback = "_message_done"; 
        if (write_file(str, implode(me["sText"], "\n")+"\n", 1)) 
        { 
                if (me["is_Modify"]) 
                        log_file(LOGFILE, sprintf("[%s] %s %s %s\n", 
                                ctime(time()), getuid(pl), 
                                me["is_NewFile"]? "+": "*", str)); 
                me["is_Modify"] = me["is_NewFile"] = 0; 
                me["sFileName"] = str; 
                _message(pl, "存檔成功\。", callback, HIDE); 
        } 
        else 
                _message(pl, "存檔失敗。", callback, HIDE); 
} // write_done()
