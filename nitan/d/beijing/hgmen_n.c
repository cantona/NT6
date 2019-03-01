inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","皇宮北門");
        set("long", @LONG
這裡便是皇宮的北門，丈高的朱紅大門敞開著，門上金色的鉚釘
閃閃發光。大門兩旁站著兩排神情嚴肅的衛兵，不停的打量著過往的
行人。燦爛的陽光直射在巍峨雄偉的古城牆上，使得城牆上方『紫禁
城』三個爍金大字顯得格外的耀眼。東廠和西廠兩個京城的特務機構
架設在皇宮北門的左右兩側。從北方穿過地安門可以到達北京的北城
郊。[2；37；0m
LONG );
        set("exits", ([
                "south" : "/d/huanggong/jingshan",
                "north" : "/d/beijing/dianmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/bing3" : 1,
                "/d/beijing/npc/yuqian1" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2800);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (objectp(ob = present("guan bing", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "伸手攔住你朗聲說道：皇宮重地，豈容尋常百姓出入。\n\n");
        if (objectp(ob = present("shi wei", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "伸手攔住你朗聲說道：皇宮重地，豈容尋常百姓出入。\n\n");
        return ::valid_leave(me, dir);
}