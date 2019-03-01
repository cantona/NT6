#include <room.h>
#include <ansi.h>
#include <getconfig.h>
inherit ROOM;

#define HEIDIAN "hengyang"
#define HEIDIAN_NAME "衡陽黑店"

int do_look(string arg);

void create()
{
    set("short", HIY"金色走廊"NOR);
        set("long", @LONG
這裡是一條金碧輝煌的走廊，前面通往拍賣休息室，牆壁上畫著
一塊黑底金字的大匾(dabian)，整個走廊靜謐嚴肅，令人不敢大聲喧
嘩。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "south"  : "/d/city/pm_road7",
        "north"  : "/d/city/pm_restroom",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_look","look");
}

int do_look(string arg)
{
    int i;
    object pms;
    string msg;
    mapping *heidian_record;

    if (arg != "dabian") return 0;
    pms = load_object("/adm/npc/feng");
    heidian_record=query(HEIDIAN, pms);
    destruct(pms);
    msg = HIC +LOCAL_MUD_NAME()+ HIY HEIDIAN_NAME HIC " 歷代店主：\n"NOR;
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    if (!sizeof(heidian_record))
        msg += HIY "目前還沒有數據。\n";
    else
    {
        msg += sprintf(HIW"%-25s%-30s%-10s%s\n"NOR,"姓名","拍賣時間","拍賣師","價格");
        for (i = 0;i < sizeof(heidian_record);i++)
            msg += sprintf(HIY"%-25s%-30s%-10s%d\n"NOR,
                   heidian_record[i]["name"]+"("+heidian_record[i]["id"]+")",
                   ctime(heidian_record[i]["time"]),
                   heidian_record[i]["pms"],
                   heidian_record[i]["value"]
                   );
    }
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    write(msg);
    return 1;
}

int valid_leave(object me, string dir)
{
       if (dir != "north") return 1;
       if (wizardp(me)) return 1;
	if( !query("is_vendor", me) )
               return notify_fail("對不起，你並不是商人，不能入內！\n");
	if( query("balance", me)<200000000 )
               return notify_fail("對不起，你的存款不足兩萬兩黃金，還是別進去了吧。\n");
	if( query("vendor_score", me)<5000 )
               return notify_fail("對不起，你的商業評價還不足5000，不能入內！\n");

	return 1;
}