// Room: /d/city/shuyuan.c

inherit ROOM;

void create()
{
	set("short", "書院");
        set("long", @LONG
這裡是書院的講堂，窗明幾凈，一塵不染。一位莊重嚴肅的老者
坐在太師椅上講學，那就是當今大儒朱先生了。在他的兩側坐滿了求
學的學生。一張古意盎然的書案放在朱先生的前面，案上擺著幾本翻
開了的線裝書籍。朱先生的身後是一個書架(shujia)講堂內多歷代楹
聯石刻，足見書院歷史的悠久。值得一提的是嵌在講堂前左壁的學規
(xuegui)。
LONG );
	set("item_desc", ([ /* sizeof() == 1 */
		"xuegui": "
		日講經書三起，日看綱目數頁。
		通曉時務物理，參讀古文詩賦。
		讀書必須過筆，會課按時蚤完。
		夜讀仍戒晏起，疑誤定要力爭。

	求學需繳學費紋銀二十兩。\n",
	]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

	set("exits", ([ /* sizeof() == 2 */
		"up"    : "/d/city/shuyuan2",
		"south" : "/d/city/dongdajie1",
	]));

	set("objects", ([ /* sizeof() == 1 */
		"/d/city/npc/zhu" : 1,
	]));

	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}