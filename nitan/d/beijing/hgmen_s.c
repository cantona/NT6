inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","皇宮正門");
        set("long", @LONG
這裏便是皇宮的正門，丈高的硃紅大門敞開着，門上金色的鉚釘
閃閃發光。大門兩旁站着兩排神情嚴肅的衞兵，不停的打量着過往的
行人。燦爛的陽光直射在巍峨雄偉的古城牆上，使得城牆上方『紫禁
城』三個爍金大字顯得格外的耀眼。從南方的金水橋可以穿越護城河
到達繁華的天安門廣場。
LONG );
        set("exits", ([
                "south" : "/d/beijing/qiao",
                "north" : "/d/huanggong/dianwai",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 2,
                "/d/beijing/npc/yuqian1" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2800);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (objectp(ob = present("guan bing", environment(me))) && dir == "north")
                return notify_fail(ob->name() + "伸手攔住你朗聲説道：皇宮重地，豈容尋常百姓出入。\n\n");
        if (objectp(ob = present("shi wei", environment(me))) && dir == "north")
                return notify_fail(ob->name() + "伸手攔住你朗聲説道：皇宮重地，豈容尋常百姓出入。\n\n");
        return ::valid_leave(me, dir);
}