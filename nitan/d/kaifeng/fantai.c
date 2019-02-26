inherit ROOM;

void create()
{
        set("short", "繁塔");
        set("long", @LONG
繁塔建於繁台之上，這是一座六角九層，八十餘米高的巨型佛塔，
極為壯觀。有詩曰『台高地迥出半天，瞭望皇都十里春』，塔高三十
餘米，青磚砌成磚雕有精美的佛像，共有一百零八種，七千餘尊。塔
內存有一百七十八塊佛經碑刻。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                "east" : __DIR__"zhulin",
                "west" : __DIR__"jiedao2",
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}