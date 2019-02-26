#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "皇宮偏殿");
        set("long", @LONG
這裏便是紫禁城的正門的大殿，尋常百姓是到不了這裏來的，如
果你以不正當的途徑到了這裏，還是趕快離開為好。
LONG );
        set("exits", ([
                "east" : "/d/beijing/hg",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuqian1" : 2,
        ]));
        set("coor/x", -200);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
}
/* void init()
{
        add_action("do_body", "body");
}
int do_body(string arg)
{
        int max;
        object ob;
        ob = this_player();

        max=query("max_qi", ob);
        set("eff_qi", max, ob);
        set("qi", max*2, ob);
        max=query("max_jing", ob);
        set("eff_jing", max, ob);
        set("jing", max*2, ob);
        set("neili",query("max_neili",  ob)*2, ob);
        set("jingli",query("max_jingli",  ob), ob);
        max = ob->max_food_capacity();
        set("food", max+random(40), ob);
        max = ob->max_water_capacity();  
        set("water", max+random(40), ob);
        ob->clear_condition();
        return 1;
} */