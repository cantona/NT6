//Room: /d/dali/shanlin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","山林");
        set("long",@LONG
你走在一片茂密的山林中，時而有飛禽走獸橫過，百鳥在林間飛
鳴，南邊烏夷部落裡的村民經常來此狩獵。山林北面不遠傳來隆隆水
聲，看來有大河流過，南邊是一片低窪的河谷盆地，頗有人煙。
LONG);
        set("objects", ([
           __DIR__"npc/lieren": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "northdown"  : __DIR__"hebian",
            "southdown"  : __DIR__"gelucheng",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6840);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}