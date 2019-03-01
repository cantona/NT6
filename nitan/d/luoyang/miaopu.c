inherit ROOM;

void create()
{
        set("short", "苗舖");
        set("long", @LONG
未入此處，清新的花香已沁人心裨。苗舖中陳列著各種名花，玲琅滿
目，令人目不暇接。其中雖不乏珍奇異種，但是最吸引人的還是一簇簇盛
放的牡丹，天下花卉以牡丹為王，而牡丹之中又以洛陽牡丹為尊，怪不得
這裡的生意總是那麼的興旺，既有外來遊客，也有當地居民，來客不分高
低貴賤，這裡的主人總是笑臉相迎。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"miaoyuan",
                  "west" : __DIR__"sroad7",
        ]));
        set("objects", ([
                __DIR__"npc/huanong" : 1,
        ]));

	set("coor/x", -6980);
	set("coor/y", 2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}