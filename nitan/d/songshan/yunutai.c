// Room: /d/songshan/yunutai.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "玉女台");
        set("long", @LONG
這理是嵩山東南的玉女台。玉女台下的石淙洞，就是“石淙會飲”
(jing)之處。兩岸石壁高聳，險峻如削，怪古嶙峋多姿，大小別致。澗
中有巨石，兩岸多洞穴，水聲石響，淙淙有聲，故名“石淙”。
LONG );
        set("item_desc", ([
                "jing" : "
    石上青苔滿布，潤水清澈見底，上空鶯歌燕舞，水中羣魚戰遊。碧
水潭中有個大石頭，獨出水面，平整如案。登上石頂眺望，周圍是水，
四面環山，紅日映染河水，微風徐徐撲面，山青水秀，鳥語花香，大有
人在書中之感。明初詩人鄭大原《遊石淙》詩云：
                  驅車未到已聞聲，隱耳輕雷更不驚。
                  石淙參差人坐立，潭並瑩激鑑真平。
                  徐風入沼迴環轉，曲水浮移委宛行。
                  敬借付君舟棹用，不教河漢隔盈盈。
    古時稱石淙潤為“水營山陣”、“天中勝景”，每逢九月九日重陽
佳節，人們攜帶酒菜，登水中石上，猜拳行令，飲覽勝景。唐代女皇武
則天，多次到石淙尋歡作樂。久視元年五月武后遊覽中嶽時，會在此台
上，笙笛歌舞，大宴羣臣，提筆賦詩，摩崖碑刻。據此，史稱“石淙會
飲”。
    唐武則天《石淙》詩云：
                  三山十洞光玄篆，玉嶠金戀鎮紫微。
                  均露均霜標勝壤，交風交雨列皇戰。
                  萬仞高崖藏日色，千尋幽潤浴雲衣。
                  且駐歡筵賞仁智，稠鞍薄晚雜塵飛。
",
        ]));
        set("exits", ([
                "northwest" : __DIR__"shandao1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "songshan");
        set("coor/x", -20);
        set("coor/y", 810);
        set("coor/z", 30);
        setup();
}
 
int valid_leave(object me, string dir)
{
        if ((random((int)me->query_skill("dodge")) <= 20) && dir=="up")    
        {
                return notify_fail("你使勁兒一蹦，離瀑布頂還有數丈遠就掉了下來，摔的鼻青臉腫。\n");
        }
        if ((random((int)me->query_skill("dodge")) <= 35) && dir=="up")    
        {
                return notify_fail("你奮力一躍，卻離瀑布頂還有一丈多遠，看來是白費力氣。\n");
        }
        if ((random((int)me->query_skill("dodge")) <= 60) && dir=="up")    
        {
                return notify_fail("你縱身而起，離瀑布頂只差一點點了，再加把勁。\n");
        }
        return ::valid_leave(me, dir);
}