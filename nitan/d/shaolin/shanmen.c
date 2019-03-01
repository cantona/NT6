// Room: /d/shaolin/shanmen.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "少林寺");
        set("long", @LONG
一個巨大的牌坊橫架在兩片山壁之間，牌坊正上方刻著三個鬥大
的字：『少林寺』。字跡有些剝落，看上去年代久遠。兩位三十來歲
的僧人手持戒刀守在山門兩側。左側立著一塊石碑。
LONG );
    set("exits", ([
        "eastup" : __DIR__"shijie8",
        "west" : __DIR__"shijie7",
    ]));
    set("outdoors", "shaolin");
    set("objects",([
        CLASS_D("shaolin") + "/xu-tong" : 1,
        CLASS_D("shaolin") + "/xu-ming" : 1,
    ]));
    setup();
}

int valid_leave(object me, string dir)
{
    object *inv;
    mapping myfam, mygen;
    int i;

/*
    if( query("gender", me) == "女性" && dir == "eastup"){
        if(objectp(present("xu tong", environment(me))))
            return notify_fail("虛通伸手攔住你白眼一翻說道：千年以來，少林向不許"
                "女流擅入。" + RANK_D->query_respect(me) +"\n請下山去吧，免得"
                "自討沒趣。\n");
        else if(objectp(present("xu ming", environment(me))))
            return notify_fail("虛明邁步擋在你身前，雙手合什說道：阿彌陀佛，"
                "這位" + RANK_D->query_respect(me) + "請留步，\n恕小寺不接待女"
                "客。女施主倘若一心向佛，何妨去峨眉山隨喜？\n");
    }
*/

    myfam=query("family", me);

    if (userp(me) && (!myfam || myfam["family_name"] != "少林派" ) && dir == "eastup") {
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
            if( query("weapon_prop", inv[i]) && query("skill_type", inv[i]) && 
               query("equipped", inv[i]) )
                if(objectp(present("xu tong", environment(me))))
                    return notify_fail("虛通攔住你說道：這位" +
                        RANK_D->query_respect(me) + "請放下兵刃。少林千年的"
                        "規矩，外客\n不得持兵刃上山。\n");
                else if(objectp(present("xu ming", environment(me))))
                    return notify_fail("虛明邁步擋在你身前，雙手合什說道：阿"
                        "彌陀佛，這位" + RANK_D->query_respect(me) + "請收起"
                        "\n兵刃。佛門清靜之地，不便隨意舞刀弄劍。還請施主鑒"
                        "諒。\n");
    }
    return ::valid_leave(me, dir);
}