// Room: /d/jiaxing/mishi.c
// Last Modified by winder on Nov. 17 2000

#define PAINTINGS        20

inherit ROOM;

int do_move(string);
int do_open(string);
int do_browse(string arg);
string look_jiaceng();
string look_hole();

int *index = ({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
string *paintings = ({
"赫然竟是畫聖吳道子的“送子天王圖”！",
"沒想到卻是唐代閻立本的“步輦圖”。",
"張擇端的“清明上河圖”！你驚呆了。",
"卻原來是唐代李思訓的“江帆樓閣圖”。",
"居然是王維的“伏生授經圖”，王維以詩著稱，工山水，卻也有如許神妙的人物畫。",
"上面題着“韓熙載夜宴圖”，竟是五代南唐畫家顧閎中的真跡。",
"乃是北宋李公麟的“五馬圖”。",
"乃是南宋梁楷的“太白行吟圖”。",
"乃是一幅“匡廬圖”，右上端題有“荊浩真跡神品”六字。",
"居然是五代關同的“山溪待渡圖”。",
"卻原來是五代李鹹熙的“小寒林圖”。",
"沒想到卻是南唐董源的“瀟湘圖”。",
"上面題着“秋山問道圖”，呀，這不是宋初名僧巨然的大作嗎？",
"北宋米友仁的“楚山清曉圖”！你驚呆了。",
"原來是南宋馬遠的“寒江獨釣圖”。",
"赫然竟是顧愷之的“鳧雁水鳥圖”！",
"乃是唐代韓幹的“照夜白”。",
"原來是北宋崔白的“寒雀圖”。",
"卻是唐末徐熙的“雛鴿藥苗圖”。",
"竟是宋徽宗親筆所畫的“雪江歸棹圖”！",
"怎麼可能？竟然是據説失傳已久的北宋范寬的真跡“溪山行旅圖”！",
});

void create()
{
        int temp, i, j;

        set("short", "密室");
        set("long", @LONG
這是一間設計精巧的密室，並不很大，但是卻不讓人覺得擁擠。地
下有一具乾枯的骸骨 (haigu)，旁邊則是一口生鏽了的大鐵箱(xiang)。
牆上有一個小小的圓孔(kong)，通過它能看到外面的情況。
LONG
        );
        set("no_clean_up", 0);

        set("item_desc", ([
                "haigu" : "一具乾枯的骸骨。\n",
                "xiang" : "一口沉重的大鐵箱，鏽跡斑斑，所幸的是箱蓋還可以打開。\n",
                "jiaceng" : (: look_jiaceng :),
                "hole" : (: look_hole :),
                "kong" : (: look_hole :),
        ]) );

        set("exits", ([
                "out": __DIR__"xiaodian",
        ]) );
        
        set("objects", ([
                CLASS_D("taohua/qu") : 1,
        ]));

        set("coor/x", 1560);
        set("coor/y", -1061);
        set("coor/z", 0);
        setup();
        for (i = 0; i < PAINTINGS; i++)
        {
                j = random(PAINTINGS);
                while (j == i)
                        j = random(PAINTINGS);
                temp = index[i];
                index[i] = index[j];
                index[j] = temp;
        }                
}

void init()
{
        add_action("do_move", ({"move", "yi"}));
        add_action("do_open", ({"open", "kai", "dakai"}));
        add_action("do_browse", ({"browse", "check", "examine", "fan", "cha", "liulan", "jiancha"}));
}

string look_jiaceng()
{
        if( query_temp("thd_jiaceng", this_player()) )
                return "這是一個精巧的設計，不打開夾層你是看不到裏面的東西的。\n";
        return "你要看什麼？\n";
}

string look_hole()
{
        "/cmds/std/look.c"->main(this_player(),"out");
        return "";
}

void delete_tiepai()
{
        delete("tiepai_got");
}

void delete_shanshui()
{
        delete("shanshui_got");
}

void delete_xishan()
{
        delete("xishan_got");
}

int do_move(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())        return notify_fail("你正忙着呢！\n");
        if (arg == "haigu") {
                if (!query("tiepai_got") && !present("qulingfeng tiepai", me)
                && !present("qulingfeng tiepai",this_object())) {
                        write("你試着挪動屍體，發現原來在屍體下面還壓着一枚鐵牌。\n");
                        set("tiepai_got",1);
                        new(__DIR__"obj/tiepai")->move(this_object());
                        remove_call_out("delete_tiepai");
                        call_out("delete_tiepai", 300);
                }
                else {
                        write("你試着挪動屍體，卻什麼也沒有發現。\n");
                }
                return 1;
        }
        return notify_fail("你要搬動什麼？\n");
}

int do_open(string arg)
{
        int thdx, thdy;
        object me = this_player();

        if (me->is_busy() || me->is_fighting())        return notify_fail("你正忙着呢！\n");
        if (arg == "xiang") {
                if( query_temp("thd_jiaceng", me)){
                        write("鐵箱已經被你打開了！\n");
                        return 1;
                }
                thdx = random(20) + 30;
                thdy = random(20) + 30;
                write("你用勁打開了箱子，發現裏面竟藏有着無數的大內密寶。
而在珠寶的下面，有一張發黃的海圖。\n");
                write("中間的一個地方用粗筆畫了個圓圈，旁邊用潦草的字跡寫着(" + thdx + "," + thdy + ")的字樣。\n");
                write("再仔細地觀察這個箱子，似乎還藏有夾層(jiaceng)。\n");
                set("thd/x", thdx, me);
                set("thd/y", thdy, me);
                set_temp("thd_jiaceng", 1, me);
                return 1;
        }
        if (arg == "jiaceng") {
                if( query_temp("thd_jiaceng", me) == 1){
                        set_temp("thd_jiaceng", 2, me);
                        set_temp("thd_shanshui", 10+random(5), me);
                        delete_temp("thd_painting", me);
                        write("你輕輕地翻開夾層，發現裏面竟然是一軸軸的畫卷(painting)，\n都是名家所做的精品。\n");
                        return 1;
                }
                else if( query_temp("thd_jiaceng", me)){
                        write("夾層已經被你打開了！\n");
                        return 1;
                }
        }
        return notify_fail("你要打開什麼？\n");
}

int do_browse(string arg)
{
        object me = this_player();
        int painting_no;

        if( query_temp("thd_jiaceng", me)<2 )
                return 0;

        if (arg != "hua" && arg != "painting")
                return notify_fail("你要翻查什麼？\n");

        painting_no=query_temp("thd_painting", me);
        addn_temp("thd_painting", 1, me);
        if( painting_no == query_temp("thd_shanshui", me) && !query("shanshui_got") && query_temp("find_shanshui", me) && !present("shanshuihua",me) && !present("shanshuihua",this_object()) )
        {
                write( "你隨手打開一軸畫卷，是一幅潑墨山水，令你覺得很奇怪的是，此畫風骨雖佳，但少了含藴韻致，不象是名家手筆。\n");
                new(__DIR__"obj/shanshui")->move(this_object());
                set("shanshui_got",1);
                remove_call_out("delete_shanshui");
                call_out("delete_shanshui", 300);
                return 1;
        }
        if (painting_no > PAINTINGS)
                return notify_fail("你都看遍了，還賴在這裏幹嘛？！\n");
        write("你隨手打開一軸畫卷，" + paintings[index[painting_no]] + "\n");
        if (painting_no == PAINTINGS && !query("xishan_got") && !present("xi shan xing lv tu", me)
        && !present("xi shan xing lv tu", this_object())) {
                new(__DIR__"obj/xishanxinglvtu.c")->move(me);
                set("xishan_got",1);
                remove_call_out("delete_xishan");
                call_out("delete_xishan", 500);
                return 1;
        }
        return 1;
}

int valid_leave(object me, string dir)
{
        delete_temp("thd_jiaceng", me);
        delete_temp("thd_shanshui", me);
        delete_temp("thd_painting", me);
        return ::valid_leave(me, dir);
}
