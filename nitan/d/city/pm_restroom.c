#include <room.h>
#include <ansi.h>
#include <getconfig.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"休息室"NOR);
        set("long", @LONG
這是一個裝飾豪華，色調溫暖的小房間，到處擺放著各種珍奇古
玩。寬大的真皮沙發柔軟舒適，大款們來到這裡都會坐下來，討論一
下泥巴商業運作情況。休息室大門通向金色走廊，另一面牆壁有一道
小門，平常緊閉著，只有在每兩月一次的泥巴黑店拍賣時，巫師才會
將之打開。一塊小小的牌子 (paizi)掛在東面牆上，這是巫師宣布黑
店拍賣底價用的。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "south"  : "/d/city/pm_road8",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_look","look");
    if (wiz_level(this_player()) > 2)
    {
        add_action("do_open","open");
        add_action("do_close","close");
    }
}

int do_open()
{
    if (query("exits/north"))
        return notify_fail("門已經是開著的了。\n");
    set("exits/north","/clone/SHOP/pmc");
    message_vision(HIY"$N輕輕一推，將通向拍賣大廳的小門開啟了。\n"NOR,this_player());
    shout(HIY + this_player()->name() +  "開啟了拍賣休息室裡那扇通往拍賣大廳的金色小門！\n" NOR);
    write(HIY + "你開啟了拍賣休息室裡那扇通往拍賣大廳的金色小門！\n" NOR);
    return 1;
}

int do_close()
{
    if (!query("exits/north"))
        return notify_fail("門已經是關著的了。\n");
    delete("exits/north");
    message_vision(HIY"$N順手一帶，將通向拍賣大廳的小門關閉了。\n"NOR,this_player());
    return 1;
}

int do_look(string arg)
{
    int i;
    string msg;
    mapping *SHOP_record;

    if (arg != "paizi") return 0;
    if (!query("exits/north"))
    {
        write("現在尚未到拍賣黑店的時間。\n");
        return 1;
    }

    SHOP_record = SHOP_D->query_SHOP();
    msg = HIC +LOCAL_MUD_NAME()+ HIY "黑店" HIC " 拍賣底價表：\n"NOR;
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    msg += sprintf(HIW"%-20s%-20s%-20s\n"NOR,"黑店ID","黑店名字","拍賣底價");
    for (i = 0;i < sizeof(SHOP_record);i++)
        msg += sprintf(HIY"%-20s%-20s%-20d\n"NOR,
            SHOP_record[i]["id"],
            SHOP_record[i]["name"],
            SHOP_record[i]["price"]
            );
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    msg += HIC "一共 " HIR + chinese_number(sizeof(SHOP_record)) + HIC " 家黑店\n";
    write(msg);
    return 1;
}