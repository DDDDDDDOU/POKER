import { createLocalVue, mount ,shallowMount} from "@vue/test-utils";
import ElementUI from "element-ui";
import blog from "../../src/components/blog";
// import image from '../../src/assets/image/poster_1.png';
// import image2 from '../../src/assets/image/poster_2.png';
const localVue = createLocalVue();
localVue.use(ElementUI);
/**spec
 * mock的axios
 * 可以根据需要添加其他函数功能
 */
const axios = {
    get: async () => "success",
    post:async ()=>"success"
};


const $router={
    push:jest.fn()
}



describe("init blog", () => {
    const wrapper = shallowMount(blog, {
        mocks: {
            axios,
        },
        localVue
    });
    wrapper.setData({
        mock:-1,
        blog: {
            blogMongo: null,
            coll_number: 0,
            com_number: 0,
            id: 0,
            is_del: 0,
            like: 0,
            post_day: "2020-09-01 08:00",
            reblog: 0,
            reblog_id: -1,
            type: 3,
            uid: 0
        },
        blogMongo: {
            comments: ['asd'],
            content: 'Hello world',
            id: 0,
            images: [],
            labels: ['ddd'],
            video: null,
            who_collect: [1],
            who_like: [1,2],
            who_reblog: []
        },
    })
    it("init state",   () => {

        /**
         * 检查data的初始状态
         */
        expect(wrapper.vm.generator({
            userAvatar: 'http://bpic.588ku.com/element_pic/01/55/09/6357474dbf2409c.jpg',
            blog: {
                blogMongo: null,
                coll_number: 0,
                com_number: 0,
                id: 0,
                is_del: 0,
                like: 0,
                post_day: "2020-09-01 08:00",
                reblog: 0,
                reblog_id: -1,
                type: 3,
                uid: 0
            },
            blogMongo: {
                comments: [],
                content: 'Hello world',
                id: 0,
                images: [],
                labels: [],
                video: null,
                who_collect: [1],
                who_like: [1,2],
                who_reblog: []
            },
            comments: [],
            reblog: {},
            reblogMongo: {},
            userName: 'weins',
            reblogUserName: '',
        })).toEqual("http://bpic.588ku.com/element_pic/01/55/09/6357474dbf2409c.jpg");

        wrapper.setData({
            mock:1
        })
        expect(wrapper.vm.generator({
            userAvatar: 'http://bpic.588ku.com/element_pic/01/55/09/6357474dbf2409c.jpg',
            blog: {
                blogMongo: null,
                coll_number: 0,
                com_number: 0,
                id: 0,
                is_del: 0,
                like: 0,
                post_day: "2020-09-01 08:00",
                reblog: 0,
                reblog_id: -1,
                type: 3,
                uid: 0
            },
            blogMongo: {
                comments: [],
                content: 'Hello world',
                id: 0,
                images: [],
                labels: [],
                video: null,
                who_collect: [],
                who_like: [],
                who_reblog: []
            },
            comments: [],
            reblog: {},
            reblogMongo: {},
            userName: 'weins',
            reblogUserName: '',
        })).toEqual("http://bpic.588ku.com/element_pic/01/55/09/6357474dbf2409c.jpg");


        expect(wrapper.vm.blog).toEqual( {
            blogMongo: null,
            coll_number: 0,
            com_number: 0,
            id: 0,
            is_del: 0,
            like: 0,
            post_day: "2020-09-01 08:00",
            reblog: 0,
            reblog_id: -1,
            type: 3,
            uid: 0
        });
        expect(wrapper.vm.blogMongo).toEqual( {
            comments: [],
            content: 'Hello world',
            id: 0,
            images: [],
            labels: [],
            video: null,
            who_collect: [],
            who_like: [],
            who_reblog: []
        });
        // expect(wrapper.vm.comments).toEqual( []);
        // expect(wrapper.vm.reblog).toEqual( {});
        // expect(wrapper.vm.reblogMongo).toEqual( {});
        // expect(wrapper.vm.username).toEqual( '');
        // expect(wrapper.vm.reblog_name).toEqual( '');
        // expect(wrapper.vm.dialogVisible).toEqual(false);
        // expect(wrapper.vm.options_flag).toEqual(false);
        // expect(wrapper.vm.showpic).toEqual("");
        // expect(wrapper.vm.tag_flag).toEqual(false);
        // expect(wrapper.vm.like_flag).toEqual(false);
        // expect(wrapper.vm.collect_flag).toEqual(false);
        // expect(wrapper.vm.share_flag).toEqual(false);
        // expect(wrapper.vm.comment_flag).toEqual(false);
        // expect(wrapper.vm.like_num).toEqual(0);
        // expect(wrapper.vm.share_num).toEqual(0);
        // expect(wrapper.vm.collect_num).toEqual(0);
        // expect(wrapper.vm.comment_num).toEqual(0);
        //
        //


    });

});

describe('test function',()=>{
    const wrapper = shallowMount(blog, {
        mocks: {
            axios,
            $router
        },
        localVue
    });

    it("test simple func",()=>{
        //generete()
        expect(wrapper.vm.maxPic(

            "{\"base64\" : \"data:image/jpeg;base64,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\"}"
       )).toEqual(true);



        //visitTag
        expect(wrapper.vm.visitTag({content:'123'})).toEqual({content:'123'});

        //comment
        wrapper.setData({
            comment_flag:true
        })
        expect(wrapper.vm.comment()).toEqual(true);
        wrapper.setData({
            comment_flag:false
        })
        expect(wrapper.vm.comment()).toEqual(true);


        //visit
        expect(wrapper.vm.visit(-1)).toEqual(1);
        expect(wrapper.vm.visit(1)).toEqual(2);


        //like
        wrapper.setData({
            mock:-1,
            collect_flag:true
        })
        expect(wrapper.vm.like()).toEqual(false);
        //collect
        expect(wrapper.vm.collect()).toEqual(false);
        //share
        expect(wrapper.vm.share()).toEqual(false);

        wrapper.setData({
            mock:1,
            like_flag:true,
            collect_flag:true
        })
        expect(wrapper.vm.like()).resolves.toBeTruthy();
        //collect
        expect(wrapper.vm.collect()).resolves.toBeTruthy();
        //share
        expect(wrapper.vm.share()).toEqual(true);



        wrapper.setData({
            mock:1,
            like_flag:false,
            collect_flag:false
        })
        expect(wrapper.vm.like()).resolves.toBeTruthy();
        //collect
        expect(wrapper.vm.collect()).resolves.toBeTruthy();




        //fresh
        expect(wrapper.vm.fresh()).resolves.toBeTruthy();

        //change
        expect(wrapper.vm.change()).toEqual(true);

        //_delete
        expect(wrapper.vm._delete()).resolves.toBeTruthy();

        //option_auth
        expect(wrapper.vm.option_auth(0)).toEqual(false);
        expect(wrapper.vm.option_auth(2)).toEqual(false);
        expect(wrapper.vm.option_auth(4)).toEqual(false);

        //option
        expect(wrapper.vm.option(0)).toEqual(0);
        expect(wrapper.vm.option(2)).toEqual(2);
        expect(wrapper.vm.option(4)).toEqual(4);

        wrapper.setData({
        blog:{
            blogMongo: null,
                coll_number: 0,
            com_number: 0,
            id: 0,
            is_del: 0,
            like: 0,
            post_day: "2020-09-01 08:00",
            reblog: 0,
            reblog_id: -1,
            type: 1,
            uid: 0
        }
        })
        // parseType2Str
        expect(wrapper.vm. parseType2Str()).toEqual('粉丝可见');
        wrapper.setData({
            blog:{
                blogMongo: null,
                coll_number: 0,
                com_number: 0,
                id: 0,
                is_del: 0,
                like: 0,
                post_day: "2020-09-01 08:00",
                reblog: 0,
                reblog_id: -1,
                type: 0,
                uid: 0
            }
        })
        // parseType2Str
        expect(wrapper.vm. parseType2Str()).toEqual('仅自己可见');
        wrapper.setData({
            blog:{
                blogMongo: null,
                coll_number: 0,
                com_number: 0,
                id: 0,
                is_del: 0,
                like: 0,
                post_day: "2020-09-01 08:00",
                reblog: 0,
                reblog_id: -1,
                type: 3,
                uid: 0
            }
        })
        // parseType2Str
        expect(wrapper.vm. parseType2Str()).toEqual('公开可见');

        expect(wrapper.vm.parseBase64(            "{\"base64\" : \"data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAYABgAAD/2wBDABQODxIPDRQSEBIXFRQYHjIhHhwcHj0sLiQySUBMS0dARkVQWnNiUFVtVkVGZIhlbXd7gYKBTmCNl4x9lnN+gXz/2wBDARUXFx4aHjshITt8U0ZTfHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHx8fHz/wAARCAFeAV4DASIAAhEBAxEB/8QAGwABAAMBAQEBAAAAAAAAAAAAAAEEBQMCBgf/xABAEAACAQMCAwQGBggHAQEBAAAAAQIDBBESIQUxQRMiMlEzYXFygZEUFSNCUqEGQ5KxwdHh8DQ1U2KCovHCJNL/xAAZAQEAAwEBAAAAAAAAAAAAAAAAAQIDBAX/xAAnEQEAAgEDBAIDAQADAAAAAAAAAQIRAxIxFCFBUQQTIjJhM0JDcf/aAAwDAQACEQMRAD8A+zAAAAADlWq9lDVjO51K168Uc+sDl9KqS8kdKVSUprVJmH9dWv6qNWt7lP8AmafC7qN5TjWhGUU21iXMDSwRHkejK4jxiPDq1OlKk5uccrEsAagwZdnxj6Tc06ErWtSlUTcXOOE8GnKUYRcpNJLm2BIDkkst7HONelLw1IP2MDpj1g8xqQku7JP2HrKAAZQyA3AySBAJAEAkARkZJAEZGV5kgAAQBIIwMASCMDAEgjAAkEACQAAAAAAAAAAAAAq3/wDhy0Vb/wBBt5gfn/CpSXG6EdUkte6z6j7DgP8Ahltj7SX7z5+24XOncxrtyhVW8XmK3xvs2fR8GpzpUIRnJybbll+sJax8b+miXbUH10fxZ9mYPG7GFzVpzqqm46fvZ6ZcuSfQIVeBeDhG2/Z1d/izfvnD6JU7ZyVPHe0rLwZXC7KdGvb6JPsqcW4xzlJNezzaNS+x9Fnqg6ieE4p4zv5gY01wxRjB3NaP39/jLy9f5HOlbcPlOn2V7qlr1RXZt5LMFZznFStP1bWZTbwvj7D3SteF1JRcKbbzp3b3CVOlw22kqNKN7qlKWumnSxqX9o6VeFRt4xhK+hTk3lJrGefr82XIWtlG4jONKcZWsc+pc/7+J1ld277Ry7VvskpZj0f/AKEKM6PaPNLiFOLdTV6aW732/OKJ+jXtajV+jXyqSdTnGr0y9vVzPNK14fSnpjO4yt3n4fyNKyhQtLWdSnOTpyepyk8tgZ8rTi/ZySry1ZWMT5L+8ndQ4pCE25ym3FKKjp2fnv6i9G+oSaxNLK1fA9fTKGqMdfelulhgRTlXUVKok46eSXez+45RqXavpwlBOg1mLxy28/ado3dCbSjVg2+SUjspJx1ZWPMDP+lXkdP/AOV1MpZedOHjcr3HE7+E8U7CenS3lpvff+hrRqQmsxnGSzjZ5PSafJoDFXFr1yX/AOTK0yfVbrO37vmWrXiM69KU504w0wcvF5M0RsBl0OLSq1qNOdDQ6nPveHfHl6izXv4W84qUZSUopqUcYe+C04xfOKGlJYSWEBmw43bycEoVcym4pY8v/TUOMbejHCjSgsPO0UdgAAAEEnGvKUYd3m2lnyImcRkh1yMmHrrY71Srl+UizZTqu4jFzk44eVJ5OevyN04w2nSmIzlqEdSSOp0sUgAAAAAAAAAAAABXvPRL3iwVb+TjbuSWWunmBjynQpXSiqWZat3nk5GrbpKcUuRkdnUqV+2+jYqJLnPbJqWbqOX2qinnbT5EzMeFY3eWgc3ThUilOKkvWjoRHwkLPMacIY0xSxtsjxc9oqL7LGrK5rPU7ADL7S6UovsotuPPs34sfkS7i6jUUZ0lJLLyoP14/v1mlgYQGfCripTjOjTbntJxXreRdSo0pwi6MZQqJLOrH5GhgYQGVSqUamM0F3paX3uS/vHzPML+lUpQg6GIVJOGnXsa2leRHZw/CvkBQtKdtcR1RoOm4ct/aVtdp3O5UxHupal5/wBTYVOCe0UvgeXb0XzpQ/ZAyXKyzCq414yS0rfkX/q+knlSmt841fkdpW1GccSpRazywdgM36rjpitfKWrLj7P5fmPqxKUHGenR5R/qaQAzqlhOcqT7X0bzjDw/zLFvRnSUlKWpN567FkAZ0LS4h+ub72p95nW6o3FSdGVGagovM1qe5cAGXTt7+OHKvnvfllf1NNEgAAAIIlFSWGsoz+I3tShVjRpPEnFy2jnl/wCCjxKPZx7dNSy02lts0s/9kTNe2VIvEzhFayl2spUknF9NXI72Vs6OqU/HL18jp9Lt9vtYfM9xr0py0xqQcvJS3MI0axbdDab2mMOpHUkjqbKJAAAAAAAAAAAAACrfNqhtzyWipfy0UNWG8PkuZEkMCepzkpyk8Prk1+GQ0U4evvFPtKdSWr6PUm/cL9nOUprVTcEuWWjDTpEWzlte2a4aB5j4UejyvCjoYpBmyqzXFVDXLR5Z25GijOl4tn+LWrtw9Agk0VAAAAAAAAAAAAAAAAAAAAAAAAUr2xjdyjLXKE4prUvJnujZUaVKNNRyoxcd/J8yyCczjCsViJyruxoScpOGXJYlmT3QpWdGlU104aW8dX0WP4lkELBHUkjqBIAAAAAAAAAAAAAVrz0S9pZK156Je0DFhW05113JzjvGPOL9Rq2me5q8WNzPVVzqOlQio+cpbY+Bo2y0uKznBlSGl108rwo9HleFGrNmT/zhe3/5L1xWVCk5tZ9RRn/nC9v/AMmhVjCUMVFFx5945dPOLY9y2v8A8c+laNW7nDWqVNLmot7nq1vFcScJR0TXQl31snjtPkmyjTnGXFFKD7spfwItfbMYnJFd0TmMLla7lbzSq0+4+Uky1GSkk08p8jhe0e2t5JeJbo4cLraqbpvnHl7C++a6m2eJV2xNcwtVq8aUqcWm5TlhJEXFzCgo6sty5Jc2caf297Kpnu0lpXtO06MJVo1Zc4rYtm0xMwjERPdxlf6FmdCrFebRapVI1YKcHlM416lGdKcJVIbrzK/CZfZ1I+TKxeYvFZnOU7YmucNIAHQzAAAAAAAAAAAAAAAAAAAI6kkdQJAAAAAAAAAAAAACteeiXtLJWvPRr3iJGUpusnrpR3jqg2/7waFo9WiS6oyoqi6Wv7SeHjQ5es1LSWqSxFxS5ZM6T37tLwvnleFHo8coo1Zs2X+cL2//ACe+LSapQS5N7nOg+34nKovDHr8MGhWowr03GayjjpWb0tEeZb2tttXPhysqVOFvBwSzJZbKcmvrfbz/AIHenZVKfdhcSUPLB7jYwhXhVhJrTzXmJpa1YjGMEWiJmc8rnQxajlZXc9PJp4+JtFa4tlXqU5N40Pf1mutpzeI28wpp2is9+E2dHsaEU/E95e0pX051bqNDVphsahUvLPt5KcJaZrqRqUnZtqUtG7MpVlQhTfcT25s4cI8NX2o6qldTjoq1Ixj1cVuz1Z2rtnNOSak9ikVnfWYjELbvxmJlcAB1sQAAAAAAAAAAAAAAAAAACOpJHUCQAAAAAAAAAAAAAq33oNll52LRWvPRL3iJIYFKm+xj35c3jT7TU4ZslF7OLxpxy/mVYyk62m3UVGLWrZYaZoWs4zmtLzh4ZjSsRLW9pmF08ShGpT0zWV5HQ8x8KN2SrXn9F7KNGEUpyw9ibi5VKk5QlByXRvmVOINfSKUUs75azzPEqqahPsPsYbpOWFk4rauJtEN4pmIloQuYScIt4lJZOzbUdlllSyqTk3201qlvGHVI831d9lUjCTUoNbpm0amKbpZ7fyxDtQu4VpOO8ZrnFlhlWnbwhJV1lz09XzPUbinVpOWrSlzy8YJraYj8uUTEZ7Jtrnt3Pu6dLxzELlTr1KbWOz5yKNoqeak5qb0ybys8iZqNGpWnUhJ05tJb8zKNW22JlpNIzMNRYayjjXuY0HFSUnqeFgUopUo9k3CONlgz76o5XMKerOlrp1NNTUmtMq0runDTp1YVG1GSbWzXkdCjRpOp9tCpolLnhfkXi9JmY7qzGEPkcZ3VKEFNzym8bbnWbxHr8Fky3Si7qNOm5OKlrntyZXUvNeE0rE8tOFSM21GSbXNeR6bSW7wUYYpzcqcpzervpQO92lK1qZWe7ncmL9plG3vh2U0+pKeTOp04vhTbis4bzj1nfh8UrWDSSzzIrqTMxH8yma4iVwAGygAAAAAAAAR1JI6gSAAAAAAAAAAAAAFW/i5UGk9Lb5+RaKt/LTQb32fTmRPCYY6hOj2joyp6GlHVKXLoaNlSVJrlql4n5sy6SX0Jam4xb8WeW/kafD25RjOUYxct9jHTxlrfhpHleFHoiPhN2LPvIaatGXNyqrJFdrtWmu2mvDTXKPrZcqTo5XaShnOFl9RmnTWcxis+wwnSzMrxbhSoRVO4ca/p57xfQ51raVC0quctUpSTbNJdlKeU4ykuvUlyi08tYWzI+mMYT9k5yz6t/TdBRg3q2T2PcLSMe2nUl9nPderqXNFNNd2OemxO0k1zXJkxpTPe3c34/VR4foVOtnGjV+RW7WLqwhVk3QhJ6XjmaataSSSgsLp0PcqMJw0SgnHyM50bbYj0t9kZmXN11KkpUVrcvCkUK9u6Loub1VJzzJmrGEYRUYrCXI51qEKzi5p915W5fU05tH9VrfbKo+1trzTTjqp1HnHl5mh6xgk0pTblSbZc6qnKOKbSb6voZ9n3FXeJScZdHuzUKs7ChObk4vL32ZTUpMzEwtW0RExKlRoupV1OU6U5ybSzvg0LlYtKq/2M80rKlSnrgnqXVs61KUasdM849TwRTTmKTHlNrZmJU6f+UP3X+872H+Ep+z+JP0SmqTp4ko+WpnujRjRhphnHk2TSkxaJn1gtaJif/XYAG7MAAAAAAAAI6kkdQJAAAAAAAAAAAAACrfLNHnjfmWite+h+JBDGkqdHs6XpY77ORocPjTil2cHDLy0zNqU5Su6UpPTKerC/DhbGpYurt2yjq9XUxp+3DW/6tAiPhJIj4Tdk+cv4wnfVNNCbXLEKUHlrm/FnqiIYlZU+xg6bjV+0nGnFbNaoy2eNlJY9ZtT4fbVJudSlGcst5ks4zjP7jxDhdtClKDhqzylJJuPdUVjy2SAybBNXlN06VNTU6rXc505NtTyv2TnSpSdN28qtd4mtLlGcdWFHO0d/2jZp8LoU6kKkHUVSGNM9W6j+H3fUdp2kJasScZOetTSTcXjG2V5AY+q6r0LWpQl2cZU3KGrVJ5alnOd3tgs8HzGdeCq1ZRjUaxKlp6LrjmXlZRhSoU6dScFQjpg1jPLHUW9o6E5yVerLXJylGWnDfwQHfWu1UMPOM+wqUOJ0a9TRGFRPGd0v4Msunmq5qWG46Xt8itR4ZSpSy3rWMaZJYwA+sqKhrcKmlNJvTyye6d9RqQjLMkmpPePlzOFTg9vOk4ZcU/wpLz8vazpDh1OFNQVSailJYWPvcwPUuJW0JaZycXjOJLGN8HeNWEnFJ7yjqXs/tlSrw1zqa1cTi34njmWIUXGdJtrFOGnZY8v5AWAAAAAAAAAAAAAAAAAAAI6kkdQJAAAAAAAAAAAAACteeiXtLJWvfQrPmBQdanFrVNdS3btOUWnlGPt9rW0+F6Yxl1ZpcP185rG+yTyZVvMzhpauIy0yI+EkiPhNWbgrmnKpOO+Ic5Nd1fE69pD8a+ZRlCnFSi68FBVNaUlnEm29/VnJy+r7eUF9qpap7+vupY2a8gNPtI63DO6WT1qXmZ9zQhd619IilJJYS6b+v1/kRLh8KlRuFb9Zrax68/v1fMC6q0HNx1bqWnHrxn9xKqRdSVNPvRSbXt/8KtzY9vWlNVNKaWY4ynJPn8so8Lh0o6nGsk3Bx8OyTcntv/u/IDQyc61elQjqqzjCPm/mUqnC1KMlGppnLPfUd99X/wDX5HqfD5Ss1bxqJeLLcc+JNfxAvpprK5HhVabjKSnFqGVJp8sHP6PN5f0iqvUsY/cU3wyeiUVW1695KcdtTTTewGnlDK8yhKyq9qpQrd3tVLDXJZzj83+XkeadjWp6EqurC6t88Javbt+YF+U4xS1SSy8bhVISlKKnFyjzSe6M6nw+vF0tVXWoSUnqk3jDztt1PVawrS7Tsq8oudXXhS07acc8fH4AaOUMmbKyupOcnUjq1ScMTlhZX/hFazvKmZKrhv7qqySxmXX4x/ZA0ySraUq1JVFWlqzNuL1NvH9+RaAAAAAAAAAAAAR1JI6gSAAAAAAAAAAAAAFe89EveLBXvPRL3gMhwt3KpJqXd3lhyL9lo0w7NYjjZGbJrF7v/eDR4e80aOPwr9xlSfyaW4aJEfCiSI+E1Zq8rOlJvWm8vPifm3/FiVnRlHS45WdXP1YKl1aV61top5jPtZSypY21P+BYt6U6aoqSfdg02360B6djRecp78+8daVCFFtwWMpL5FKhbVaV1Kq4tqU+suS739D12FZWVakk3JruZlu/awL4MWnY3aVJaXTxKWrFTo8HtWd7GeVUlh5z3v8Ab/MDYBl2NvcUaNRVU03KON/nyO1xC5+17BSVR+CWrurbyfrAvAz5xualFyTk5qo9CXdyltvyPdzC6ll0JKPh2fvb9fIC6DOcL3DxOaWUllRzjfd/kRGF9GCbk5PTvHu5zv8A0A0gZ0I32IuUknzawvX+/YsNVHGuo6l+H5dALIM7hUbmNKf0pzcm9tWeXxNEAAAAAAAAAAQBIIAEkdQEBIAAAAAAAAAAAAAV7z0S94sFe89EveAyp3VKlWVLRJyf4Ymjb+NGDdxhO8lGUZd5qOU/Z/M3qHjiQLhEfCSRHwkjHk7xV6/ptElPT6t9mji5X6hCK7dSc8vKeywv7+JvYGAKNTtnZUVHX2jWG8PPhZ1sFV+i0+2z2jWXkskgAQAJBAAkAAAAAAAAAAAAAAAAAAQAAAAABALmwJAAAAAAAAAAAAACveeiXvFgr3nol7wHz9zGTu5PsoyWqMU+RuW/jiZNanV7dyi6klqWIrZY2/qa1v44gXCI+EkiPhAkAgCSAAAAAAAASQCBIAJAAAAAAAAAAACCSAAAAAAAQuoEepA9AAkAAAAAAAAAAAK956Je8WCveeiXvAZFarKN5SgqcWpYzJrkadDxxMqtr+m0sQbjtmW+2/8AQ1aHjiBcIj4STzHwgSCAQJAAAAAAAAIRJ56gewASONe5pW8NVapGEfWzLrfpHZwbUNdT2LBY4laUbucI145jjbDxgzqv6L036G4lH1SWTG1rZxDSsVx3JfpP+C3+cjm/0lrvw0aa9uTlP9G7qPgqUp/HBxlwW9g/RxfskjKb2jltFdNYl+kV50hSX/F/zPK/SG8a/Vr/AIlZ8KvP9H/siFwu8z6CXzRH2W9rbaLS/SC86uH7J7XH7vzh+yU/qq8S3oSH1ddJ70n80RN7RzKdtJX48fuesab+B1hx6r96nD4GeuH3P+mv2ke1w+t10r4lftmPKdlPTUjx1fep/md6fGbeTxPVExXaOPOaz6jtaW1CpBym5PD5ZL11bT5VtpUfRUqsK0NVOSlHzR0KnD4RhRaisLUWWdUTmMuSYxOAmPUiKzueupMISACQAAAAAAAAAAAr3nol7xYK956Je8BjVlm+prTL7ryvVn+Zq2/jRSbh2sU3PV5LOC7Q9JEC29keI7xJzkiHhRA9AAAAAJBBIAAAQQz0QBKexxuLmlbxzUljPJdWep1FSpynLlFZPmKsq3Eb7sKcsTnu5fhiUtfHaGlKbu88NKvxa2qTS1OLXmWKfEac3iLyjN4lwShb2OujqdSHik34ilwNtVatNvbGxhbdWW0VravZ9UqqlFNdRKOrco289dDu80zqqk4tbFd+eWezHDrKOE2jxnZY5ntvXHKR5cXp5PJS0ekx/XSMu5iRTrbSkWVnC2ZxuIOSeFuZasTeqadpV6cssVFuRCM4yeYsmWXth+054mZjEt3CHem0+iM6lVlb3VSlJ7Texp04SU5NxfLyMnikHGvRqrOqMs/A6NLnEky+qsHqtlLzbO/N4ONlHRZUk/w5LEVselXiHFbmXojqSR1LqpAAAAAAAAAAAAACveeiXvFgr3nol7wGVO313cK23cWOf9DQoeNGbGs4qpOEdfe07e00bSWvRLGNSyBaEPCicMRXdKgSMDBIBDAwwGQTgbgCAAAAAp8SbjZ1Ph+8y/0bgp3N3WazJaYr+/ka3EKbqWdWK54yYv6O1eyvq9B/rYqUfav/AEx/7Ibx/nL6G4pKtQnTlyksGXacMpWVapJydTV5rkbBwqpasN8y2pXyzpaeFOhBRnUin1ydHtscqDTrzT89mWWvijlx2bTPd4jLTujrGany5+Ry055HnvRZXMwiYiVg8tkRnqXIh89iZVwicdRyeVszseJLJlenmF6y5asPcr3NurhRjjqdqiO9lByeZdCaZm2F7TiMriikoxXI6Hlc2z0enDjCOpJHUkSAAAAAAAAAAAAAFe89EveLBXvPRL3gMidSNOFaTnJaZLL22NG1lqcJeayZVb0Vwny1rksmpZeClj8K/cBfIj4SSI+FASAAAAAAAAQSAIwQegBzkso+a4pZVrK4V3bPTFSypL7p9M0ecJpprKMrVyvS21k2f6Q0KqUblOjPq+cWXqtalXoylRqxnjrF5Kt1wK0rtygnSl/s5fIyr3gVe0pyrUK+tR3f3ZIrO7GJXiKTPZctLhSnOVTGOeUXoy2ynqR8/wAIuJRqypVXn29TWjDm4Safl0ObhvNV6GZLKDyitCtKDxOL9qOquoy6r4k5hnMS95Go88/I8y2jtzRVOHXURLY5RllZJ1ZJ5Rh5ayy9bw0U/aVaENc8F7oa6NO+5TUt4THkegDrYhHUkjqBIAAAAAAAAAAAAAV7z0S94sFe89EveAyHRlUhXhGWlyllPJo2kdPZxfRYKMqsqdzCEaWVPxS8jQoeOIFwiPhRJEfCgJAAAAAAAAAAAAAQc+UjqeJrbJEgiJwjUhKEllSWGEydSIGRV4RRt5uvS1auW75HFycdjWrT7rT5GLVklJ6d0cutXbOYdelabdpWKVf7rZYlTpVFvFe1GO66j1OlG/UGlKfdMoaWr6akKCj4akl+Z6jT07ym5fAofWNNffH1lSw1rL4hnMStzxF6vmeXJNbPKKL4jS/EcHxKnGeIPxbY9ZMQTEw36Eo0489zsquZGNRqyaLlKTOuK4jDlmctJVEz1nJUg2d4ssh1I6hDqBIAAAAAAAAAAAAAV7z0S94sFe89EveAodpCMtLks+RboeOJmzjmU46sKWVq1cs4NKh40EzELhEfCSRHwhCQAAAAAAAAAAAAAgkAccPkNLOkl1IRUV6tPKMypYT1SlTa36M23FMjREi1YtHdatprw+ZrW1aPipSfsWSpOlJc6cl/xPsHSizz2ETL6YbRrz6fGOm+kJfI8dhWl4aNR/8AFn2jowXNo86KK+/H5jZSvMp+6Z8Pk4cNuqn3NHvMuWnBuykp1Ja5fkj6DNBffielOh/qR+ZatqR5Z2veynTtdK5FiFHCO6lT6Si/idE0aRaJ8s8S5RpnRRwesgshJHUZC5gSAAAAAAAAAAAAAFe89EveLBXvPRL3gMC6dKMZSqxlKKm8aDatnmUWZqb1y70Y999cdUadv44gXCI+Ek8x8KA9A86iUwJBGRkCQRkZQEgjK8yQAAAgA8TqRgsyaREzEcj2eepUq8Rpw8K1FOrxCrPw7ew5b/K068d2tdG9mrOpGCzKSRwqX9KHrMeVWcnlyZ49py2+ZeeOzor8aPLSnxN/dSK87+tLrgqg57at7cy1jSpHh0deo/vEOpN/eZ4Bk0xD1rl+J/Ma5fiZ5AMQ9a5eZKqzXJngE5MQ6q4qrlUl+0e1eV1+tl8yuC0XtHEq7K+ln6dcdKr+SNHh1WdajKVSWp6sIxTX4T/h5e8/4HX8XUtbUxMsNetYp2hoAA9RxAAAAAAAAAAAFe89EveLBXvPRL3gMOvpxPVDtI633YvHka9v44mRXbqatNfscTa1fLyNWDag3ndRf7iJnCeV4heExIX9xD7+r2o70uKy0rXTT91nNHytOeW06F4dpQhVrVO00SaljE3yjjocqqqVLWjGlVkvtHvl5cd1z9mD39NtqktUlOL/AL8jq7i1ml9pjTy5o1jV058qTS2MYVK/a1a1GpTrJQhpc468Zw9yx22i5q6oxWV+Pfb/ANR6zZOLWqOHvzJlOzm5Sk6bcub8yfsp7V229Ka1fQalvOr9pN5UtWebFxHt4W2KjXZeKXPOy9Zc7azjjwbf7Tx9NtqaxCPyjgidbTjmU7LenmlipxFVo1U9UcaN/wC+homS76nF5pUIQfR4OU7+tP72PZsY2+Xpxx3aRoXlsSqRgu9JL2srVeIUoeF6mZEqk5PLe54Oa/zLT+sYbV+NHleq8SqT2j3V6ipOrObzKTPAOS17W5lvWla8QAAouAAAAAAAAAAAAAAAAGvwn/Dy95/wMg1+E/4eXvP+B2fD/wBHP8j9GgAD1nAAAAAAAAAAAAV7z0S94sHipTjUjiXIDK7GnLnFc8lheCXuv9x3dpH7smiJW7UJd5PZkW4THLCC5FxcOqv70Pmz0uGVfxw/M8T6rz4el9lfaiC+uFzf6yPyPS4VJ/rV8ifov6R9tGcMml9UvrW/6k/VK/1v+pPT6npH3U9swGp9VQXOrL5HpcKpLnOf5F+k1UffRkg11wyh+KfzPS4bb/7n8Sek1EdTRjA21w62/A/myVw+2/0/zY6O/tHU1YYN76Fbr9VElWtv/ow+Rbore0dTX0wMA+gVtR6Uofso9dhSXKnD5E9FPtHUx6fOg+iVOn+CPyPWmK6L5Fui/p1P8fNk6ZPkmfSaV5IYJ6H+o6mfT5xU5vlCXyPXYVX+qn+yz6LAwT0VfaOpn0+fVrXf6mfyJVncP9VI3wT0VfaOpt6YSsLl/qn80T9X3P8Ap/mjcyMlujojqLsT6uufwr9on6tuPKPzNoE9JpnUXYy4ZX/2fMv2NvK3pSjNrLlnYtA0p8emnOYZ21bXjEpABuzAAAAAH//Z\"}"
        )).toEqual(            "data:image/jpeg;base64,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"
        );
        //
        //
        // //share()
        // expect(wrapper.vm.share()).toEqual(true);
        // expect(wrapper.vm.blog.share_flag).toEqual(true);
        //
        //
        // //change()
        // expect(wrapper.vm.change()).toEqual(true);
        // expect(wrapper.vm.blog.share_flag).toEqual(false);
        //
        // //collect()
        // expect(wrapper.vm.collect()).toEqual(true);
        // expect(wrapper.vm.blog.collect_flag).toEqual(true);
        // expect(wrapper.vm.blog.collect).toEqual(254);
        // expect(wrapper.vm.collect()).toEqual(false);
        // expect(wrapper.vm.blog.collect_flag).toEqual(false);
        // expect(wrapper.vm.blog.collect).toEqual(253);
        //
        //
        // //like()
        // expect(wrapper.vm.like()).toEqual(true);
        // expect(wrapper.vm.blog.like_flag).toEqual(true);
        // expect(wrapper.vm.blog.like).toEqual(1454);
        // expect(wrapper.vm.like()).toEqual(false);
        // expect(wrapper.vm.blog.like_flag).toEqual(false);
        // expect(wrapper.vm.blog.like).toEqual(1453);
        //
        //
        //
        // //maiPic()
        // expect(wrapper.vm.showpic).toEqual("");
        // expect(wrapper.vm.maxPic({image:image})).toEqual(true);
        // expect(wrapper.vm.showpic).toEqual(image);
        //
        //
        // //coment()
        // expect(wrapper.vm.comment()).toEqual(true);

    })


})
