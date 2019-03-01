// Room: /city/kedian4.c 
// SMALLFISH 1995/12/04 
 
#include <ansi.h> 
#include <room.h>  

inherit ROOM;

int is_chat_room() { return 1; }  

void create() 
{
        set("short", "大隱閣");
        set("long", @LONG
這裡是揚州客店附設的餐廳大堂，往來的旅人來到客店住宿歇腳，
大多會選擇在此點幾個具有揚州特色的小菜，就著溫熱的黃酒小酌幾
杯，以驅散周身的疲累。現在尚未到用餐時間，是以偌大的廳內空盪
盪的，連侍候客人的店小二也不知躲到哪去了。靠牆豎著一塊留言板，
上面密密麻麻寫著許多過往客人留下的手跡。
LONG );

        set("no_fight", 1);
        set("no_drift", 1);
        set("no_steal", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1); 
        set("exits", ([
                "north"   : "/d/city/kedian",
        ]));
        set("objects", ([
                "/adm/npc/huangdaxian" : 1,
        ]));

	set("coor/x", 10);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();

}
