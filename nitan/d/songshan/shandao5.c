// Room: /d/songshan/shandao5.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "勝觀山道");
        set("long", @LONG
你走在嵩山勝觀峯山道上，遙望太室，少室兩山間有一關口。那就
是軒轅關。站在此處，正可飽覽嵩山八景的“軒轅早行”(jing)。
LONG );
        set("item_desc", ([
                "jing" : "
    軒轅關又名“娥嶺關”。兩崖怪石嵯峨，山勢雄偉險要，石塞嶙峋
似劍，道路曲折盤旋，為洛都東南險關要道，是歷代兵家必爭之地。
    軒轅關因山路曲折旋繞，故名“十八盤”。早晨霧遮山腰，行人來
往其中，由下邊向上看，好像神仙騰空駕雲一樣，故有“軒轅早起上雲
端”之説。若站在關口，北視關下，可以看到霧浪翻滾，雲煙繚繞，瞬
息萬變，氣象萬千。

    詩人劉生題《軒轅道》詩日：
                    陡仄軒轅道，翠屏列上巔。
                    高峯常疑日，密樹不開天。
                    風急摧殘葉，關峽鎖雲煙。
                    早行憑眺望，靄靄白雲連。

    軒轅關上的山崖下，噴流着一股清泉，名日：“劍引泉”。傳説：
漢高祖劉邦率領大軍，攻秦奪潼關，路過這裏時，人因馬乏，滴水不見，
部下一個急將，在關上寫了一首打油詩：
                    峨嶺似火口，滴水難以瞅。
                    過此喉冒煙，此道不可走。
    劉邦見到此詩，抬腳將詩抹去，撥劍闢進山崖，結果引出一股泉水，
故名“劍引泉”。\n",
        ]));
        set("exits", ([
                "northup"   : __DIR__"chaotian",
                "southwest" : __DIR__"fawangsi",
                "southdown" : __DIR__"tieliang",
        ]));
        set("outdoors", "songshan");
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 820);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}