//Room: qunyulou.c

#include <ansi.h>

inherit ROOM;

int check_container(object ob);

void create()
{
        set("short", "羣玉樓");
        set("long", 
"羣玉樓是長安城首屈一指的大妓院。這裏不是普通人能來的地方，如果你不\n" 
"是富甲一方的財主，如果你不是雄霸一方的幫主掌門，如果你不是王公貴族，就\n" 
"連進這個門也別想。樓中僱的打手便有四名在這兒守着，不是有頭有臉的見了這\n" 
"陣仗早就繞開了去。大門貼着告示(gaoshi)一張，又高掛兩幅長聯：\n" 
HIR"             銷"HIG"              春\n\n"NOR
HIR"             魂"HIG"              色\n\n"NOR
HIR"             蝕"HIG"              無\n\n"NOR
HIR"             骨"HIG"              邊\n"NOR          
        );
        set("exits", ([ /* sizeof() == 2 */
                "north" : "/d/changan/qixiang4",
                "south" : "/d/changan/qunyulou1",
        ]));
        set("item_desc", ([
                "gaoshi": HIY @TEXT
規定:
１．不可以帶武器上樓。
２．不許鬧事，否則後果自負。
TEXT NOR
        ]) );
        set("objects", ([
                "/d/changan/npc/dashou" : 4,
        ]) );

        set("NONPC",1);
        set("coor/x", -10710);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{    
        object ob;
        object *inv;
        int i;
        if (dir == "south" &&
            objectp(ob = present("da shou", this_object())) &&
            living(ob))
        {
                if (wizardp(me))
                        return ::valid_leave(me, dir);

                if( query("gender", me) == "女性" )
                        return notify_fail(ob->name() +
                               "一把抓住了你，説道:“這裏不是女人"
                               "該來的地方，你別進去。”\n");
                inv = all_inventory(me);
                for(i = 0; i < sizeof(inv); i++)
                {
                        if( query("weapon_prop", inv[i]) )
                                return notify_fail(ob->name() +
                                                   "一把抓住了你，説道：“咱們這裏是有"
                                                   "規矩的地方，不準帶武器進入。”\n");
                }
        }
        return 1;
}