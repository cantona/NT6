//insert.c
#pragma optimize
#include <dbase.h>

inherit F_CLEAN_UP;

int do_insert(string arg)
{
        mapping cards;
        string *dirs, dir;
        int i;

        if( !arg ) return notify_fail("你要插入什麼？\n");

        cards = environment(me)->query_cards();
        if( mapp(cards) ) {
                dirs = keys(cards);
                if( member_array(arg, dirs)!=-1 ) dir = arg;
                else for(i=0; i<sizeof(dirs); i++)
                        if( arg==cards[dirs[i]]["name"] || member_array(arg, cards[dirs[i]]["id"])!=-1 ) {
                                dir = dirs[i];
                                break;
                        }
                if( !dir ) return notify_fail("你要插入什麼？\n");
        
                if( environment(me)->insert_card1(dir) ) {
                        message_vision("$N將" + cards[dir]["name"] + "插入。\n", me);
                        return 1;
                }
        }

        return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : open <door> 或 <方向>
 
這個指令可以讓你打開門.
 
HELP
    );
    return 1;
}