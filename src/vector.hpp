#include <initializer_list>
#include <stdexcept>

template <typename T>
class Vector {
public:
    // Constructors
    Vector() {
    }

    Vector(size_t sz, const T& val = T()) {
        for (size_t i = 0; i < sz; ++i) {
            PushBack(val);
        }
    }

    Vector(std::initializer_list<T>&& list) {
        for (const T& val : list) {
            PushBack(val);
        }
    }

    Vector(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector(Vector&& other) {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // operator=

    Vector& operator=(const Vector& other) {
        Vector to_swap(other);
        Swap(to_swap);
        return *this;
    }

    Vector& operator=(Vector&& other) {
        Vector to_swap(std::move(other));
        Swap(to_swap);
        return *this;
    }

    // Getters
    size_t GetSize() const {
        return size_;
    }

    size_t GetCapacity() const {
        return capacity_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    void Swap(Vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    T& Front() {
        if (IsEmpty()) {
            throw std::underflow_error("Call to Front() on an empty vector");
        }
        return data_[0];
    }

    T& Back() {
        if (IsEmpty()) {
            throw std::underflow_error("Call to Back() on an empty vector");
        }
        return data_[size_ - 1];
    }

    const T& Front() const {
        if (IsEmpty()) {
            throw std::underflow_error("Call to Front() on an empty vector");
        }
        return data_[0];
    }

    const T& Back() const {
        if (IsEmpty()) {
            throw std::underflow_error("Call to Back() on an empty vector");
        }
        return data_[size_ - 1];
    }

    // opeartor[]
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Modifiers
    void PushBack(const T& value) {
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            ResizeCapacity(new_capacity);
        }
        data_[size_++] = value;
    }

    void PopBack() {
        if (size_ == 0) {
            throw std::underflow_error("PopBack() called on an empty vector");
        }
        --size_;
    }

    void Clear() {
        size_ = 0;
    }

    void ShrinkToFit() {
        ResizeCapacity(size_);
    }

    // Destructor
    ~Vector() {
        delete[] data_;
    }

private:
    void ResizeCapacity(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        if (data_) {
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }

    T* data_{};
    size_t size_{};
    size_t capacity_{};
};
