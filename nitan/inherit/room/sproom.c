// pigtest room

#include <pig.h>

inherit "/inherit/room/pigroom";

string look_table();
string look_scoreboard();
string look_rules();

void create()
{
        set("short", "拱豬房");
        set("long", @LONG
        這是一間專門為拱豬而特別設計的拱豬房。房間裏面燈火通明，彷彿永
遠準備着為拱豬狂們服務似的。房間的中心放着一張用百年老松樹木材特製的拱
豬桌(table)，周圍放着四把楠木靠背椅。桌子上擺着一本記分簿(scoreboard)，
北邊的牆上貼着一張紙(paper)。
LONG
        );
        set("pigging", 1);

        set("item_desc", ([
                "table" : (: look_table :),
                "scoreboard" : (: look_scoreboard :),
                "paper" : "請務必讀 help pig_cmds 和 help pig_rules。\n",
        ]));

        set("exits", ([
                "north": "/d/city/duchang2",
        ]));
        set("no_fight", "1");

        setup();
}

string look_table()
{
        if( query_temp("pigging_seat", this_player()) )
                return table_str(query_temp("pigging_seat", this_player()));
        return table_str("");
}

string look_scoreboard()
{
        return scoreboard_str();
}

int valid_leave(object me, string dir)
{
        if( query_temp("pigging_seat", me) )
                return notify_fail("先離開拱豬桌才能行動。\n");
        return ::valid_leave(me, dir);
}