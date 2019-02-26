// Room: /d/wuyi/wuyigong.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "武夷宮");
        set("long", @LONG
武夷宮坐落在大王峯南麓，為武夷山門户。漢武帝遣使節在此設壇
祭祀武夷君。唐天寶年間，曾就近洲渚創建天寶殿；後改為會仙觀，宋
大中祥符二年，奉旨擴建，增修屋宇三百餘，規模宏大，富麗堂皇。南
宋紹聖二年，又大修宮殿，並改名為衝佑觀，為南宋九大名觀之一。朱
熹、陸游、辛棄疾等均在此任過提舉或主管，並在此着書賦詩。元泰定
五年改稱萬年宮。明代戚繼光路經武夷，留有《題萬年宮壁》詩：一劍
橫空星斗寒，甫隨平虜復徵蠻。他年覓取封侯印，願向君王換此山。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : "/d/yanping/shandao1",
                "south" : __DIR__"1qu",
                "north" : __DIR__"path2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
