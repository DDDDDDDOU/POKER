// import share from "../../src/components/share";
// import { shallowMount, createLocalVue, mount } from "@vue/test-utils";
// import ElementUI from "element-ui";
// const localVue = createLocalVue();
// localVue.use(ElementUI);
//
// const axios = {
//     get: async () => "success",
//     post:async ()=> "success"
//
//
// };
// describe("init share", () => {
//     const wrapper = shallowMount(share, {
//         mocks: {
//             axios
//         },
//         localVue
//     });
//     it("init state", () => {
//
//
//         /**
//          * 检查data的初始状态
//          */
//         expect(wrapper.vm.comment_to_flag).toEqual(false);
//
//     });
//
//     it("func",()=>{
//         expect(wrapper.vm.submit()).toEqual(true);
//     })
// });






import { createLocalVue, mount } from "@vue/test-utils";
import ElementUI from "element-ui";
import blog from "../../src/components/blog";
// import image from '../../src/assets/image/poster_1.png';
// import image2 from '../../src/assets/image/poster_2.png';
const localVue = createLocalVue();
localVue.use(ElementUI);
/**
 * mock的axios
 * 可以根据需要添加其他函数功能
 */
const axios = {
    get: async () => "success",
    post:async ()=>"success"
};






describe("init blog", async () => {
    const wrapper = mount(blog, {
        mocks: {
            axios,
        },
        localVue
    });

    it("init state",   () => {

        /**
         * 检查data的初始状态
         */
        expect(wrapper.vm.blog).toEqual( {});
        expect(wrapper.vm.blogMongo).toEqual( {});
        expect(wrapper.vm.comments).toEqual( []);
        expect(wrapper.vm.reblog).toEqual( {});
        expect(wrapper.vm.reblogMongo).toEqual( {});
        expect(wrapper.vm.username).toEqual( '');
        expect(wrapper.vm.reblog_name).toEqual( '');
        expect(wrapper.vm.dialogVisible).toEqual(false);
        expect(wrapper.vm.options_flag).toEqual(false);
        expect(wrapper.vm.showpic).toEqual("");
        expect(wrapper.vm.tag_flag).toEqual(false);
        expect(wrapper.vm.like_flag).toEqual(false);
        expect(wrapper.vm.collect_flag).toEqual(false);
        expect(wrapper.vm.share_flag).toEqual(false);
        expect(wrapper.vm.comment_flag).toEqual(false);
        expect(wrapper.vm.like_num).toEqual(0);
        expect(wrapper.vm.share_num).toEqual(0);
        expect(wrapper.vm.collect_num).toEqual(0);
        expect(wrapper.vm.comment_num).toEqual(0);




    });

});