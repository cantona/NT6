//Room: /d/dali/lushui.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","瀘水沿岸");
        set("long", @LONG
一條土路沿著瀘水縱貫谷地南北，腳下瀘水滔滔流去，長年累月
沖刷著谷中大地，東面碧羅雪山、西面的高黎山皆高聳蔽日。土路北
通此谷中心大鎮巴的甸，南連數個烏夷小部落。
LONG );
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/badidian",
            "south"      : "/d/dali/atoubu",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
        (CLASS_D("ultra") + "/huang")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("huang shang", this_object())))
                return sort_string(msg, 60, 4);

        if (! ob->is_fighting())
                msg += "有一人沿江來回踱步，時而低頭冥思，時而舉頭遠"
                       "望，似乎在想什麼要緊的問題。";
        else
                msg += "只見一人正在與" +
                       (ob->is_fighting(this_player()) ? "你" : "人") +
                       "激戰，進退之間，幹凈利索，沒有一點花巧。";

        return sort_string(msg, 60, 4);
}