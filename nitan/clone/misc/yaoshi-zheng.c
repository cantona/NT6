#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT "煉藥師証" NOR, ({ "yaoshi zheng", "yaoshi", "zheng" }));
        set_weight(1);
        set("level", 1);
        set("long", WHT "這是一枚紅底金邊的煉藥師証，等級 "+query("level")+" 品，由煉藥師協會頒發。\n" NOR);
        set("unit", "枚");
        set("value", 5);
        set("material", "steal");
        set("no_sell", "這年頭，你把吃飯的家伙也拿來賣錢？");
        setup();
}

void enable()
{
        set_name(HIR+chinese_number(query("level"))+"品" WHT "煉藥師証" NOR, ({ "yaoshi zheng", "yaoshi", "zheng" }));
        set("long", WHT "這是一枚紅底金邊的煉藥師証，等級 "+query("level")+" 品，由煉藥師協會頒發。\n" NOR);
}
