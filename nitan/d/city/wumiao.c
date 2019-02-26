// wumiao.c
#include <room.h>
inherit ROOM;
int is_chat_room() { return 1; }

void create()
{
        set("short", "武廟");
        set("long", @LONG
這裏是揚州嶽王廟的正殿，內有岳飛像，像上方懸掛岳飛手書『
還我河山』的橫匾。殿兩側壁上嵌着『精忠報國』四個大字。武人到
此，都放下武器，畢恭畢敬地上香禮拜。旁邊似乎有一道側門。
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);

        set("valid_startroom", 1);
	set("objects", ([
		__DIR__"obj/box" : 1,
		"/u/luoyun/qiandao" : 1,
	]));

	set("exits", ([
		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
                "northwest": "/d/wizard/guest_room",     
	]));
        create_door("northwest", "竹門", "southeast", DOOR_CLOSED);
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();

        ("/adm/npc/nanxian")->come_here();
}

int valid_leave(object me, string dir)
{
        if (dir == "northwest" && ! playerp(me) && ! me->is_chatter())
                return 0;
                
        return ::valid_leave(me, dir);
}