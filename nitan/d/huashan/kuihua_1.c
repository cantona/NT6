#include <ansi.h>
inherit ROOM;

#define JIASHA    "/clone/lonely/book/kuihua1"

void create()
{
        set("short", "山崖");
        set("long", @LONG
這是華山後山的陡峭山崖，左上方便是華山派掌門嶽不羣的居室，
居室的窗户正對着你的頭頂。
LONG );
        set("exits",([
                "east" : __DIR__"songlin4",
        ]));
        setup();
}

void init()
{
        object me = this_player(), ob;

        ob = find_object(JIASHA);
        if (! ob) ob = load_object(JIASHA);

        add_action("do_look", "view");
               add_action("do_look", "wang");

        if (! environment(ob) &&
            ! query("begin") &&
            ! query("over") &&
            query("gender", me) == "無性" )
        {
                set("jiasha", 1);
                tell_object(me, HIB "你剛到這裏，忽然聽見上方窗户傳來陣陣耳"
                                "語，不禁想朝窗户望(view)去！\n" NOR);
        }
        return 0;
}

int do_look(string arg)
{
        object me = this_player();

        if (arg != "window" && arg != "chuanghu" && arg != "chuang")
                return notify_fail("你要看什麼？\n");

        if (query("over") || ! query("jiasha"))
                return notify_fail("一扇緊閉着的窗户，沒什麼好瞧的。\n");

        if (query("begin"))
                return notify_fail("窗户裏兩個人影正在談話，要偷聽就別動。\n");

        if( query("gender", me) != "無性" )
                return notify_fail("一扇緊閉着的窗户，沒什麼好瞧的。\n");

        message_vision(HIB "$N" HIB "望窗户瞧去，只見窗前立着兩個淡淡的人影，正在"
                       "低聲細語，$N" HIB "忍耐不住好奇，悄悄\n的走到窗前偷聽兩人"
                       "的對話。\n" NOR,me);
        remove_call_out("do_talk1");
        call_out("do_talk1", 4, me);
        set("begin", 1);
        me->start_busy(43);
        return 1;
}

int do_talk1(object me)
{
        message_vision( WHT "\n只聽得一位女子的聲音説道：“師哥，我覺得你近來神色"
                        "不對，是不是練那紫霞神功有\n些兒麻煩？可別太求精進，惹出"
                        "亂子來。”聽聲音似乎是華山掌門夫人甯中則。\n" NOR, me);
        remove_call_out("do_talk2");
        call_out("do_talk2", 4, me);
        return 1;
}

int do_talk2(object me)
{
        message_vision( WHT "\n又聽得一位尖聲尖氣的聲音説道：“沒有啊，我練功順利"
                        "得很。”那聲音依稀便是華山\n的掌門嶽不羣，你不竟大吃一驚"
                        "。\n" NOR, me);
        remove_call_out("do_talk3");
        call_out("do_talk3", 4, me);
        return 1;
}

int do_talk3(object me)
{
        message_vision( WHT "\n那女子又道：“你別瞞我，為甚麼你近來説話的嗓子變了"
                        "，又尖又高，倒像女人似的。”\n" NOR, me);
        remove_call_out("do_talk4");
        call_out("do_talk4", 4, me);
        return 1;
}

int do_talk4(object me)
{
        message_vision( WHT "\n那男子怒道：“胡説八道！我説話向來就是這樣的。”\n"
                        NOR, me);
        remove_call_out("do_talk5");
        call_out("do_talk5", 4, me);
        return 1;
}

int do_talk5(object me)
{
        message_vision( HIB "\n你聽得那男子説這句話，嗓聲果然相當尖，確像是個女子"
                        "在大發脾氣。\n" NOR, me);
        remove_call_out("do_talk6");
        call_out("do_talk6", 4, me);
        return 1;
}

int do_talk6(object me)
{
        message_vision( WHT "\n那女子接着説道：“還説沒變？你一生之中，就從來沒對"
                        "我這樣説過話。我倆夫婦多年，\n你心中有甚麼解不開的事，何"
                        "以瞞我？”\n" NOR, me);
        remove_call_out("do_talk7");
        call_out("do_talk7", 4, me);
        return 1;
}

int do_talk7(object me)
{
        message_vision( WHT "\n那男子又道：“有甚麼解不開的事？嗯，嵩山之會不遠，"
                        "左冷禪意圖吞併四派，其心昭\n然若揭。我為此煩心，那也是有"
                        "的。”\n" NOR,me);
        remove_call_out("do_talk8");
        call_out("do_talk8", 4, me);
        return 1;
}

int do_talk8(object me)
{
        message_vision( WHT "\n那女子哼了一聲，道：“我看還不止於此。”\n" NOR, me);
        remove_call_out("do_talk9");
        call_out("do_talk9", 4, me);
        return 1;
}

int do_talk9(object me)
{
        message_vision( WHT "\n那男子尖聲道：“你便是瞎疑心，此外更有甚麼？”\n"
                        NOR, me);
        remove_call_out("do_talk10");
        call_out("do_talk10", 4, me);
        return 1;
}

int do_talk10(object me)
{
        message_vision( WHT "\n那女子聲音十分平靜，説道：“我説了出來，你可別發火"
                        "。我知道你是冤枉了衝兒。那\n日衝兒受傷昏迷，我替他止血治"
                        "傷之時，見到他身上有件袈裟，寫滿了字，似乎是劍法\n之類。"
                        "第二次替他換藥，那件袈裟已經不見了，其時衝兒仍然昏迷未醒"
                        "。這段時候之中，\n除了你我二人，並無別人進房。這件袈裟可"
                        "不是我拿的。”\n" NOR, me);
        remove_call_out("do_talk11");
        call_out("do_talk11", 6, me);
        return 1;
}

int do_talk11(object me)
{
        message_vision( WHT "\n那男子幾次插口説話，但均只含糊不清的説了一兩個字，"
                        "便沒再説下去……\n" NOR, me);
        remove_call_out("do_talk12");
        call_out("do_talk12", 4, me);
        return 1;
}

int do_talk12(object me)
{
        message_vision( WHT "\n那女子語聲漸轉柔和，説道：“師哥，我華山一派的劍術"
                        "，自有獨到的造詣，紫霞神功\n的氣功更是不凡，以此與人爭雄"
                        "，自亦足以樹名聲於江湖，原不必再去另學別派劍術。\n只是近"
                        "來左冷禪野心大熾，圖並四派。華山一派在你手裏，説甚麼也不"
                        "能淪亡於他的手\n中。咱們再聯絡了泰山、恆山、衡山三派，到"
                        "時以四派鬥他一派，我看還是佔了六成贏\n面，就算真的不勝，"
                        "大夥兒轟轟烈烈的劇鬥一場，將性命送在嵩山，也就是了，到了"
                        "九\n泉之下也不致愧對華山派的列祖列宗。”\n" NOR, me);
        remove_call_out("do_talk13");
        call_out("do_talk13", 6, me);
        return 1;
}

int do_talk13(object me)
{
        message_vision( WHT "\n那男子大聲道：“你怎知我在學辟邪劍法？你……你……"
                        "在偷看我嗎？”\n" NOR, me);
        remove_call_out("do_talk14");
        call_out("do_talk14", 4, me);
        return 1;
}

int do_talk14(object me)
{
        message_vision( WHT "\n那女子説道：“我又何必偷看這才知道？你説話的聲音，"
                        "就已經全然變了，人人都聽得\n出來，難道你自己反而不覺得？"
                        "每天早晨，你被窩裏總是落下了許多鬍鬚……”\n" NOR, me);
        remove_call_out("do_talk15");
        call_out("do_talk15", 4, me);
        return 1;
}

int do_talk15(object me)
{
        message_vision( WHT "\n那男子尖叫一聲，問道：“你瞧見了？語音甚是驚怖。”"
                        "\n" NOR, me);
        remove_call_out("do_talk16");
        call_out("do_talk16", 4, me);
        return 1;
}

int do_talk16(object me)
{
        message_vision( WHT "\n那女子歎道：“我早瞧見了，一直不説。你粘的假須，能"
                        "瞞過旁人，卻怎瞞得過和你做\n了幾十年夫妻的枕邊之人？”\n"
                        NOR,me);
        remove_call_out("do_talk17");
        call_out("do_talk17", 4, me);
        return 1;
}

int do_talk17(object me)
{
        message_vision( WHT "\n那男子見事已敗露，無可再辯，隔了良久，問道：“旁人"
                        "還有誰知道了？”\n" NOR, me);
        remove_call_out("do_talk18");
        call_out("do_talk18", 4, me);
        return 1;
}

int do_talk18(object me)
{
        message_vision( WHT "\n那女子説道：“沒有，珊兒和平之也不知道”\n" NOR, me);
        remove_call_out("do_talk19");
        call_out("do_talk19", 4, me);
        return 1;
}

int do_talk19(object me)
{
        message_vision( WHT "\n那男子沉吟片刻，説道：“好，我聽你的勸，這件袈裟，"
                        "我立即毀去，再慢慢想法替令\n狐沖洗刷清白。這路劍法，今後"
                        "也不練了。”\n" NOR, me);
        remove_call_out("do_talk20");
        call_out("do_talk20", 4, me);
        return 1;
}

int do_talk20(object me)
{
        object ob;
        int exp, pot, sc;

        exp = 10000 + random(3000);
        pot = 1000 + random(300);
        sc = random(50);

        ob = find_object(JIASHA);
        if (! ob) ob = load_object(JIASHA);

        if (! environment(ob))
        {
                message_vision( HIR "\n$N" HIR "大吃一驚，便想出聲阻止，劍譜乃不世之物，"
                               "管他有益有害，嶽老賊可無權毀去。便\n在此時，只聽得窗子呀"
                               "的一聲打開，$N" HIR "急忙縮頭，眼前紅光一閃，那件袈裟飄"
                               "將了下來，\n跟着窗子又即關上。眼看那袈裟從身旁飄過，$N" HIR
                               "伸手一抓，差了數尺，沒能抓到。頓時\n$N" HIR "將生死置之"
                               "度外，右手搭在崖上，左腳拚命向外一勾，只覺腳尖似乎碰到了"
                               "袈裟，立\n即縮將回來，當真幸運得緊，竟將那袈裟勾到了，沒"
                               "落入天聲峽下的萬仞深淵中。\n\n" NOR, me);
                set("over", 1);
                delete_temp("jiasha");
                ob->move(me, 1);

                if( !query("skybook/xiaoao/baodian", me) )
                {
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("score", sc, me);
                        tell_object(me, HIW "你成功的取得了葵花寶典！\n" NOR + HIC "通"
                                        "過這次的歷練，你獲得了" + chinese_number(exp) +
                                        "點經驗、" + chinese_number(pot) + "點潛\n能以及"
                                        + chinese_number(sc) + "點江湖閲歷。\n\n" NOR);
                        set("skybook/xiaoao/baodian", 1, me);
                } else
                        tell_object(me, HIC "你得到了一件袈裟。\n\n" NOR);
        } else
        {
                message_vision( HIR "\n$N" HIR "大吃一驚，便想出聲阻止，劍譜乃不世之物，"
                               "管他有益有害，嶽老賊可無權毀去。便\n在此時，只聽得窗子呀"
                               "的一聲打開，$N" HIR "急忙縮頭，眼前紅光一閃，那件袈裟飄"
                               "將了下來，\n跟着窗子又即關上。眼看那袈裟從身旁飄過，$N" HIR
                               "伸手一抓，差了數尺，沒能抓到。袈裟\n頓時落入天聲峽下的萬"
                               "仞深淵中。\n\n" NOR, me);
                set("over", 1);
                delete_temp("jiasha");
        }
        return 1;
}