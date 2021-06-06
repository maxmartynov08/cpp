#pragma once
#include <vector>
#include <iterator>
#include <utility>


namespace linq {

    namespace impl {

        template<typename T>
        struct functor {
            functor(T t): t(t) {}
            functor(functor&& f) {
                std::swap(f.t, t);
            }
            functor(const functor&) = delete;
            bool operator() (T tt) {
                return tt != t;
            }

            T t;
        };

        template<typename T>
        class take_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T, typename R, typename F>
        class select_enumerator;


        template<typename T>
        class enumerator {
        public:
            enumerator() = default;
            enumerator(enumerator &&) = default;
            enumerator(const enumerator &) = delete;
            enumerator &operator=(const enumerator &) = delete;
            virtual ~enumerator() = default;

            virtual operator bool() const = 0;
            virtual enumerator &operator++() = 0;
            virtual const T &operator*() = 0;

            std::vector <T> to_vector() {
                std::vector <T> res;
                while (*this) {
                    res.push_back(**this);
                    ++(*this);
                }
                return res;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = **this;
                    it++;
                    ++(*this);
                }
            }

            auto take(int number) {
                return take_enumerator<T>(*this, number);
            }

            auto drop(int number) {
                return drop_enumerator<T>(*this, number);
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, std::move(func));
            }

            auto where_neq(T t) {
                return where([t](T cur) { return cur != t; });
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(T t) {
                return until([t](T cur) { return cur == t; });
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, std::move(func));
            }
        };


        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int number) : parent(parent), number(number) {}
            take_enumerator(take_enumerator &&) = default;

            virtual operator bool() const {
                return number > 0 && (bool) parent;
            }

            virtual enumerator<T> &operator++() {
                --number;
                if (number > 0)
                    ++parent;
                return *this;
            }

            virtual const T &operator*() {
                return *parent;
            }

        private:
            enumerator<T> &parent;
            int number;
        };


        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int number) : parent(parent), number(number) {
                while ((bool) parent && number > 0) {
                    ++parent;
                    --number;
                }
            }
            drop_enumerator(drop_enumerator &&) = default;

            virtual operator bool() const {
                return (bool) parent;
            }

            virtual enumerator<T> &operator++() {
                ++parent;
                return *this;
            }

            virtual const T &operator*() {
                return *parent;
            }

        private:
            enumerator<T> &parent;
            int number;
        };


        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F _func) : parent(parent), func(std::move(_func)) {
                while ((bool) parent && !func(*parent))
                    ++parent;
            }
            where_enumerator(where_enumerator &&) = default;

            virtual operator bool() const {
                return (bool) parent;
            }

            virtual enumerator<T> &operator++() {
                ++parent;
                while ((bool) parent && !func(*parent))
                    ++parent;
                return *this;
            }

            virtual const T &operator*() {
                return *parent;
            }

        private:
            enumerator<T> &parent;
            F func;
        };


        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F func) : parent(parent), func(std::move(func)) {}
            until_enumerator(until_enumerator &&) = default;

            virtual operator bool() const {
                return (bool) parent && !func(*parent);
            }

            virtual enumerator<T> &operator++() {
                if ((bool) parent && !func(*parent))
                    ++parent;
                return *this;
            }

            virtual const T &operator*() {
                return *parent;
            }

        private:
            enumerator<T> &parent;
            F func;
        };


        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U> &parent, F _func) : parent(parent), func(std::move(_func)) {
                cache = func(*parent);
            }
            select_enumerator(select_enumerator &&) = default;

            virtual operator bool() const {
                return (bool) parent;
            }

            virtual enumerator<T> &operator++() {
                ++parent;
                if ((bool)parent)
                    cache = func(*parent);
                return *this;
            }

            virtual const T &operator*() {
                return cache;
            }

        private:
            enumerator<U> &parent;
            F func;
            T cache;
        };


        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter beg, Iter end) : beg(beg), end(end) {};
            range_enumerator(range_enumerator &&) = default;

            virtual operator bool() const {
                return beg != end;
            }

            virtual enumerator<T> &operator++() {
                ++beg;
                return *this;
            }

            virtual const T &operator*() {
                return *beg;
            }

        private:
            Iter beg;
            Iter end;
        };
    }

    template<typename Iter>
    auto from(Iter beg, Iter end) {
        return impl::range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(beg, end);
    }
}