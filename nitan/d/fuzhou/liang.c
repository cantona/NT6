// room: liang.c

#include <ansi.h>
#include <room.h>

#define JIASHA    "/clone/lonely/book/kuihua3"

inherit ROOM;

void create()
{
        object item;
        set("short","密室房樑");
        set("long", @LONG
你現在在密室的房樑上四下觀瞧，周圍都是些爛木頭破磚瓦。突然
你瞟見犄角旮旯處有一件袈裟。
LONG );
        set("exits", ([
                "down" : __DIR__"mishi",
        ]));
        set("objects", ([
                //__DIR__"obj/jiasha" : 1,
                "/d/xingxiu/npc/snake" :1,
        ]));
        set("coor/x", 1820);
        set("coor/y", -6312);
        set("coor/z", 10);
        setup();
        item = find_object(JIASHA);
        if( !objectp(item) || !environment(item) ) {
                item = get_object(JIASHA);
                item->move(this_object());
                item->start_borrowing();
        }
}


void init()
{
        object me = this_player(), ob;
        int exp, pot, sc;

        exp = 10000 + random(3000);
        pot = 1000 + random(300);
        sc = random(50);

        ob = find_object(JIASHA);
        if (! ob) ob = load_object(JIASHA);

        if (! objectp(ob))
                return 0;

        if (! objectp(present("jia sha", this_object())))
                return 0;

        if( !query("skybook/xiaoao/baodian", me) )
        {
                addn("combat_exp", exp, me);
                addn("potential", pot, me);
                addn("score", sc, me);
                tell_object(me, HIY "\n你剛躍上房樑，頓時發現一件袈裟擺放其中。\n\n"
                                NOR + HIW "你成功的找到了葵花寶典！\n" NOR + HIC
                                "通過這次的歷練，你獲得了" + chinese_number(exp) +
                                "點經驗、" + chinese_number(pot) + "點潛\n能以及"
                                + chinese_number(sc) + "點江湖閱歷。\n\n" NOR);
                set("skybook/xiaoao/baodian", 1, me);
        } else
                tell_object(me, HIY "\n你剛躍上房樑，頓時發現一件袈裟擺放其中。\n\n" NOR);
}

void reset()
{
        object item;
        ::reset();
        item = find_object(JIASHA);
        if( !objectp(item) || !environment(item) ) {
                item = get_object(JIASHA);
                item->move(this_object());
                item->start_borrowing();
        }
}
