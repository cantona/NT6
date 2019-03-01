// c_doc.c 制作幫派文件

void doc_edit( string str );
int main( object me )
{
        if( !query("bunch", me) || query("bunch/level", me)<7 )
                return 0;
                
        me->edit( (: doc_edit :) );
        return 1;
}

void doc_edit( string str )
{
        write_file("/help/"+query("bunch/bunch_name", this_player()),str,1);
        return;
}


int help( object me )
{
        write( "
        c_doc: 幫主編寫幫派文件。
        可在文件裡編寫幫規, 幫派歷史, 等資料。
        玩家 help <幫派中文名稱> 即可閱讀幫派文件。

");
        return 1;
}
