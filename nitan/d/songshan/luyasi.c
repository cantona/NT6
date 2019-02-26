// Room: /d/songshan/luyasi.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "盧崖寺");
        set("long", @LONG
忽聽水聲如雷，懸練峯下一座高大的石崖峭壁上，兩條玉龍直掛下
來，雙瀑並泄，屈曲迴旋，飛躍奔逸，水花映日，淡淡冕生。唐玄宗年
間，有一個被封為諫儀大夫的盧鴻乙，不原做官，來此隱居，廣招天下
才子，在此講學，此崖遂稱為“盧崖”，鴻乙隱居處稱為“早堂”。鴻
乙仙遊之後，玄宗改“草堂”為“盧崖寺”。嵩山八景的“盧崖瀑布”
(jing)便在此間。
    瀑布斜過就是勝觀峯。瀑布之側有路可上。
LONG );
        set("item_desc", ([
                "jing" : "
    盧崖寺北峽谷內，有一股泉水，終年不斷，平時泉水瀉崖下，好似
千丈珠廉掣掛長空。澎湃之聲，如虎豹怒吼，如雷聲轟鳴。太陽直射上
面，奇光異彩，燦爛奪目，瞬息萬變，氣象萬千。水珠積流，形成水潭，
潭上獨出一個黛色圓石，明朝袁宏道在上面刻有“墨浪石”三個大字。
水流其上，好似墨浪。人稱此景為“盧崖瀑布墨浪流”，亦稱“珍珠倒
卷廉”。
    明高出《盧崖瀑布》詩云：
                太室東來第幾峯，孤崖側削半芙蓉。
                為看飛瀑三千尺，直透春雲一萬重。
",
        ]));
        set("exits", ([
                "southwest" : __DIR__"shandao1",
                "up"        : __DIR__"tieliang",
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