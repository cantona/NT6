#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name(NOR + CYN "「毒經上篇」" NOR, ({ "du jing1", "jing1", "book1" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", CYN "這是一本薄薄的小冊，上面密密麻麻的寫滿了各種用毒\n"
                            "的基本方法和毒藥的配方。你可以用讀(read)一讀。\n" NOR);
                set("value", 100);
                set("no_sell", "我…我的天…連五毒教的東西你都敢拿來賣？");
                set("material", "silk");
                set("skill", ([
                        "name"         : "poison",
                        "exp_required" : 500,
                        "jing_cost"    : 20,
                        "difficulty"   : 20,
                        "max_skill"    : 49,
                ]));
        }
}

void init()
{
        add_action("do_read", "read");
}

int do_read(string arg)
{
        if (arg == "jing1" || arg == "book1")
                return notify_fail(NOR + CYN "\n"
"                                ┏┓\n"
"┏━━━━━━━━━━━━━━━┫┣━━━━━━━━━━━━━━━┓\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┃┃                              ┃\n"
"┃         配       方          ┃┃       密   藥   配   方      ┃\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┃┃                              ┃\n"
"┃ 赤蠍粉：斷腸草、蛇信子、毒囊 ┃┃  五聖散：分取斷腸散、腐肉膏  ┃\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┃┃                              ┃\n"
"┃ 孔雀膽：腐骨草、千日醉、毒囊 ┃┃  鶴頂紅、孔雀膽、赤蠍粉各一  ┃\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┃┃                              ┃\n"
"┃ 鶴頂紅：蛇信子、千日醉、毒囊 ┃┃  份，外加金蛇毒液調製，即可  ┃\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┃┃                              ┃\n"
"┃ 斷腸散：斷腸草、穿心蓮、毒囊 ┃┃  煉成而成。如將密藥配法外泄  ┃\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┃┃                              ┃\n"
"┃ 腐肉膏：腐骨草、穿心蓮、毒囊 ┃┃  者當殺無赦。                ┃\n"
"┃                              ┃┃                              ┃\n"
"┃                              ┣┫                              ┃\n"
"┗━━━━━━━━━━━━━━━┛┗━━━━━━━━━━━━━━━┛\n"
"\n\n" NOR);
}
