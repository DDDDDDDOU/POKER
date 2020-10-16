import Vue from 'vue'
import App from './App.vue'
import './index.css'
import './css1.css'
import './css2.css'
import ElementUI from 'element-ui'
// import './index2.css'
import router from "./Router";
import VueResource from 'vue-resource'

Vue.use(VueResource);
Vue.use(ElementUI);
Vue.config.productionTip = false;

new Vue({
  data: function(){
    return{
      logged:false,
      superuser:false
    }

  },

  render: h => h(App),
  router,
}).$mount('#app')
