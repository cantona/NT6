//Cracked by Roath
// /kungfu/class/emei/zhou.h
// yasuko: 2000/08/17
// mantian: may/21/2001
// kick out ppl for those learn pxj after bai zhou
// xiaojian for fixing all of the bugs June 22,2001
// xQin 06/01 add a log for expelled students 
#include <ansi.h>

void init()
{
        object ob,me;
        ob=this_player();
        me=this_object();

        ::init();

        set_heart_beat(1);

        if(interactive(ob)
                 && query("family/family_name", ob) == "峨嵋派"
                 && query("gender", ob) == "無性"
                && (int)ob->query_skill("pixie-jian", 1) >=1) {
                if( !query("pxj_warning", ob)){
                        set("pxj_warning", 1, ob);
                        command("hmm");
                        command("say 正邪不兩立,你為何去偷學辟邪劍法? 趕快改過自新,否則下次見到你定不輕饒!\n");
                } else {
                command("look "+getuid(ob));
                command("hmm "+getuid(ob));
                command("sneer "+getuid(ob));
                command("say "+RANK_D->query_rude(ob)+"即然學了九陰真經上的功夫，為何去學辟邪劍法，嫌我教的不夠好？");
                command("expell"+query("id", ob));
                command("say 滾吧！");
                delete("pxj_warning", ob);
                write_file("/kungfu/class/emei/zhou_log.c",
                sprintf("%s(%s)wasexpelledbyzhouduetopxj%d(%d).\n",query("id", this_player()),ctime(time())));
                }
        }
}
string ask_jiuyin()
{
        object ob,me=this_player();
        if( query("family/master_name", me) != "周芷若" )
                return RANK_D->query_respect(this_player())+"與我素不相識，何出此言呢？";
        ob=new(__DIR__"obj/jiuyin-paper");
        if (present("juan pian",me)) return "咦，你身上不是帶着九陰真經了嗎，怎麼還來問我？";
        if (!ob) return "嗯，借給你倒是沒問題，只是剛被別的弟子借走了，你過一陣再來問問吧。";
        if( !query("jiuyin/first", me)){
                command ("say 你是第一次來借九陰真經吧？\n
            這束絹片是密抄本的九陰真經，原來藏在倚天劍裏，其實也不是什麼大不了的東西，
            你拿去翻翻吧。\n
            為師以前年輕不懂事，只知道照着書上的招式修煉(xiulian)，雖然進展很快，但
            是越練到後來，越是兇險。如果不能潛心領悟(lingwu)九陰真經中的真諦，終究無
            法有所大成。當然，領悟的話會慢很多。你要是有什麼不明白的，就直接過來跟我
            學吧。\n");
                set("jiuyin/first", 1, me);
        }
        ob->move(me);
        message_vision("$n遞給$N一束絹片。\n",me,this_object());
        command("rumor"+query("name", me)+"弄到了九陰真經密抄本。");
        return "記住師父的話，千萬不要貪功急進，否則到時候就後悔莫及了。";
}

void attempt_apprentice(object ob)
{
    mapping fam;
    int last_betray,shen;
        
        //xiaojian: added a check before recruiting, i.e. won't recruit pxj dizi.

                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("ah"+query("id", ob));
                        command("say 小女子與朝廷素無往來，不知這位大人到此有何公幹？");
                        return;
                 }

        // Yinli and Qianzhu-wandu: by yasuko
        if ((int)ob->query_skill("qianzhu-wandu", 1) >=1 ) {
                command("sneer"+query("id", ob));
                command("say 這位" + RANK_D->query_respect(this_player())
                + "與殷姑娘淵源非淺，在下可不敢誤人子弟。");
                return;
        }
        // Emei dizi(Linji-zhuang & Pixie-jian)：by yasuko
        if( query("family/family_name", ob) == "峨嵋派"){
                if ((int)ob->query_skill("linji-zhuang", 1) < 90) {
                        command ("say " + RANK_D->query_respect(this_player()) +
                                 "的臨濟莊尚欠火侯， 不宜學習上乘武功。\n");
                        return;
                }
                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("sigh4 " );
                        command("say 這位" + RANK_D->query_respect(this_player())
                                + "既然不稀罕本門的武功，又何必來找我呢？");
                        return;
                }
        }
        // Betryer
        else {
                // Ppl who has betraied zhou and left from emei
                last_betray=query("zhou-betray", ob);
                if( last_betray>0 && last_betray != query("betrayer", ob )
                 && query("combat_exp", ob) >= 10000){
                        command ("say " + RANK_D->query_respect(this_player()) +
                        "既然叛出峨嵋, 此刻想回卻已晚了. \n");
                        command ("say " + RANK_D->query_respect(this_player()) + "是"
                        +query("family/family_name", ob)+"高手，本派可不敢收留！");
                        return;
                }
                // Gaibang Hinghand
                if( query("family/family_name", ob) == "丐幫" && query("rank", ob)>1){
                        command("say " + RANK_D->query_respect(ob) + "是丐幫高手，恕我不能收你。");
                        return;
                }
                // Pixie-jian: by yasuko
                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("ah"+query("id", ob));
                        command("say 小女子與朝廷素無往來，不知這位大人到此有何公幹？");
                        return;
                 }
                // Peaceful life 1: by yasuko
                shen=query("shen", ob);
                if (shen >0) {
                        if (random(shen) >= 1000 ) {
                                command("xixi"+query("id", ob));
                                command("say " + RANK_D->query_respect(this_player()) + 
                                "俠名遠播，這師徒之稱實在是折殺小女子了。");
                                return;
                        }
                }
                if (shen <0) {
                        shen = 0 - shen;
                        if (random(shen) >= 1000 ) {
                                command("hmm" );
                                command("say 素聞" + RANK_D->query_respect(this_player()) + 
                                "是黑道里響噹噹的人物，你若是真能洗心革面，那我就收下你。");
                                return;
                        }
                }
                // Peaceful life 2: by yasuko
                if( random(query("PKS", ob)/query("death_times", ob))>10){
                        command("lazy");
                        command("say 這位" + RANK_D->query_respect(this_player()) + 
                        "怎麼滿臉的殺氣？小女子怕得很，請改日再來吧。");
                        return;
                }
        }
        // Giving everybody one chance to enter emei
        if ((int)ob->query_skill("claw", 1) < 40) {
                command("say 我看你是來學九陰真經上的功夫吧，先去學點兒基本爪法再來吧。");
                return;
        }
        if ((int)ob->query_skill("jiuyin-baiguzhao", 1) < 40) {
                command("say 我看你是來學九陰真經上的功夫吧，先去學點兒基本的九陰爪再來吧。");
                return;
        }
        command("say 好吧，你就跟我這兒學吧。"); 
        command("say 不過你可記住了, 要是你今後背叛師門, 我可不會再收你.\n");
        command("recruit "+query("id", ob));
        set("emei", 1, ob);
        set("zhou-betray",query("betrayer",  ob), ob);
        command("whisper"+query("id", ob)+
                        " 下次來找我時，到九老洞口叫一聲，“有侶乎？”我就會找人帶你進來.\n");
}
