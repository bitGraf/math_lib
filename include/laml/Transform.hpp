#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include <cmath>

namespace laml {
    namespace transform {

        template<typename T>
        void create_projection_orthographic(Matrix<T, 4, 4>& mat, T left, T right, T bottom, T top, T znear, T zfar) {
            laml::fill(mat, constants::zero<T>);

            mat[0][0] = constants::two<T> / (right - left);
            mat[1][1] = constants::two<T> / (top - bottom);
            mat[2][2] = constants::two<T> / (zfar - znear);

            mat[3][0] = -(right + left) / (right - left);
            mat[3][1] = -(top + bottom) / (top - bottom);
            mat[3][2] = -(zfar + znear) / (zfar - znear);

            mat[3][3] = constants::one<T>;
        }

        template<typename T>
        void create_projection_perspective(Matrix<T, 4, 4>& mat, T vertical_fov, T aspect_ratio, T znear, T zfar) {
            laml::fill(mat, constants::zero<T>);

            //const T tan_half = static_cast<T>(tan(vertical_fov * constants::deg2rad / 2.0));
            const T tan_half = tan(vertical_fov * constants::deg2rad<T> / constants::two<T>);

            mat[0][0] = constants::one<T> / (aspect_ratio * tan_half);
            mat[1][1] = constants::one<T> / tan_half;
            mat[2][2] = -(zfar + znear) / (zfar - znear);
            mat[2][3] = -constants::one<T>;
            mat[3][2] = -constants::two<T> * zfar * znear / (zfar - znear);
        }

        template<typename T>
        void create_view_matrix_from_transform(Matrix<T, 4, 4>& view, const Matrix<T, 4, 4>& transform) {
            // assume no scale is applied to the camera transform!!
            // V = inv(T x R) = inv(R) x inv(T) = transpose(R) x (-T)
            Matrix<T, 4, 4> inv_rot(laml::transpose(transform));
            inv_rot.c_41 = constants::zero<T>;
            inv_rot.c_42 = constants::zero<T>;
            inv_rot.c_43 = constants::zero<T>;
            Matrix<T, 4, 4> inv_translate(constants::one<T>);
            inv_translate.c_14 = -transform.c_14;
            inv_translate.c_24 = -transform.c_24;
            inv_translate.c_34 = -transform.c_34;
            view = mul(inv_rot, inv_translate);
        }

        template<typename T, size_t size>
        Vector<T, size> transform_point(const Matrix<T, size, size>& mat, const Vector<T, size>& vec) {
            Vector<T, size> res;
            for (size_t i = 0; i < size; i++) {
                res[i] = constants::zero<T>;
                for (size_t j = 0; j < size; j++) {
                    res[i] = res[i] + vec[j] * mat[j][i];
                }
            }
            return res;
        }
        template<typename T>
        Vector<T, 3> transform_point(const Matrix<T, 4, 4>& mat, const Vector<T, 3>& vec, T w) {
            Vector<T, 3> res(
                mat.c_11 * vec.x + mat.c_12 * vec.y + mat.c_13 * vec.z + mat.c_14 * w,
                mat.c_21 * vec.x + mat.c_22 * vec.y + mat.c_23 * vec.z + mat.c_24 * w,
                mat.c_31 * vec.x + mat.c_32 * vec.y + mat.c_33 * vec.z + mat.c_34 * w);
            return res;
        }
        template<typename T>
        Vector<T, 4> transform_point(const Matrix<T, 4, 4>& mat, const Vector<T, 4>& vec) {
            Vector<T, 4> res(
                mat.c_11 * vec.x + mat.c_12 * vec.y + mat.c_13 * vec.z + mat.c_14 * vec.w,
                mat.c_21 * vec.x + mat.c_22 * vec.y + mat.c_23 * vec.z + mat.c_24 * vec.w,
                mat.c_31 * vec.x + mat.c_32 * vec.y + mat.c_33 * vec.z + mat.c_34 * vec.w,
                mat.c_41 * vec.x + mat.c_42 * vec.y + mat.c_43 * vec.z + mat.c_44 * vec.w);
            return res;
        }

        // convert to quaternion
        template<typename T>
        Quaternion<T> quat_from_mat(const Matrix<T, 3, 3>& mat) {
                       const T one = constants::one<T>;
                       const T two = constants::two<T>;
                       const T four = static_cast<T>(4.0);
                       const T one_fourth = one / four;
                       T tr = trace(mat);
                       Quaternion<T> res;
                       if (tr > 0) {
                           T S = sqrt(tr + one) * two; // S = 4*qw
                           res.w = one_fourth * S;
                           res.x = (mat.c_32 - mat.c_23) / S;
                           res.y = (mat.c_13 - mat.c_31) / S;
                           res.z = (mat.c_21 - mat.c_12) / S;
                       }
                       else if ((mat.c_11 > mat.c_22) && (mat.c_11 > mat.c_33)) {
                           T S = sqrt(one + mat.c_11 - mat.c_22 - mat.c_33) * two; // S = 4*qx
                           res.w = (mat.c_32 - mat.c_23) / S;
                           res.x = one_fourth * S;
                           res.y = (mat.c_12 + mat.c_21) / S;
                           res.z = (mat.c_13 + mat.c_31) / S;
                       }
                       else if (mat.c_22 > mat.c_33) {
                           T S = sqrt(one + mat.c_22 - mat.c_11 - mat.c_33) * two; // S = 4*qy
                           res.w = (mat.c_13 - mat.c_31) / S;
                           res.x = (mat.c_12 + mat.c_21) / S;
                           res.y = one_fourth * S;
                           res.z = (mat.c_23 + mat.c_32) / S;
                       }
                       else {
                           T S = sqrt(one + mat.c_33 - mat.c_11 - mat.c_22) * two; // S = 4*qz
                           res.w = (mat.c_21 - mat.c_12) / S;
                           res.x = (mat.c_13 + mat.c_31) / S;
                           res.y = (mat.c_23 + mat.c_32) / S;
                           res.z = one_fourth * S;
                       }
                       return res;
        }

        // Create various 4x4 transformation matrices
        template<typename T>
        void create_transform_rotation(Matrix<T, 4, 4>& mat, T yaw, T pitch, T roll) {
            T C1, C2, C3, S1, S2, S3;
            C1 = cosf(yaw * constants::deg2rad<T>);
            C2 = cosf(pitch * constants::deg2rad<T>);
            C3 = cosf(roll * constants::deg2rad<T>);
            S1 = sinf(yaw * constants::deg2rad<T>);
            S2 = sinf(pitch * constants::deg2rad<T>);
            S3 = sinf(roll * constants::deg2rad<T>);

            mat = Matrix<T, 4, 4>(constants::one<T>); // create identity matrix
            mat[0][0] = C1 * C3 - S1 * S2 * S3;
            mat[0][1] = -C2 * S3;
            mat[0][2] = -S1 * C3 - C1 * S2 * S3;

            mat[1][0] = C1 * S3 + S1 * S2 * C3;
            mat[1][1] = C2 * C3;
            mat[1][2] = -S1 * S3 + C1 * S2 * C3;

            mat[2][0] = S1 * C2;
            mat[2][1] = -S2;
            mat[2][2] = C1 * C2;
        }
        template<typename T>
        void create_transform_rotation(Matrix<T, 3, 3>& mat, T yaw, T pitch, T roll) {
            T C1, C2, C3, S1, S2, S3;
            C1 = cos(yaw * constants::deg2rad<T>);
            C2 = cos(pitch * constants::deg2rad<T>);
            C3 = cos(roll * constants::deg2rad<T>);
            S1 = sin(yaw * constants::deg2rad<T>);
            S2 = sin(pitch * constants::deg2rad<T>);
            S3 = sin(roll * constants::deg2rad<T>);

            mat = Matrix<T, 3, 3>(constants::one<T>); // create identity matrix
            mat[0][0] = C1 * C3 - S1 * S2 * S3;
            mat[0][1] = -C2 * S3;
            mat[0][2] = -S1 * C3 - C1 * S2 * S3;

            mat[1][0] = C1 * S3 + S1 * S2 * C3;
            mat[1][1] = C2 * C3;
            mat[1][2] = -S1 * S3 + C1 * S2 * C3;

            mat[2][0] = S1 * C2;
            mat[2][1] = -S2;
            mat[2][2] = C1 * C2;
        }
        template<typename T>
        void create_ZXZ_rotation(Matrix<T, 3, 3>& mat, T alpha, T beta, T gamma) {
            T C1, C2, C3, S1, S2, S3;
            C1 = cosd(alpha);
            C2 = cosd(beta);
            C3 = cosd(gamma);
            S1 = sind(alpha);
            S2 = sind(beta);
            S3 = sind(gamma);

            // mat[j][i] = c_ij (zero-indexed)
            mat = Matrix<T, 3, 3>(constants::one<T>); // create identity matrix
            mat[0][0] = C1*C3 - S1*C2*S3;
            mat[0][1] = S1*C3 + C1*C2*S3;
            mat[0][2] = S2*S3;

            mat[1][0] = -C1*S3 - S1*C2*C3;
            mat[1][1] = C1*C2*C3 - S1*S3;
            mat[1][2] = S2*C3;

            mat[2][0] = S1*S2;
            mat[2][1] = -C1*S2;
            mat[2][2] = C2;
        }
        template<typename T>
        void create_transform_rotation(Matrix<T, 4, 4>& mat, const Quaternion<T>& rot_quat) {
            mat = Matrix<T, 4, 4>(constants::one<T>);
            mat[0][0] = 1 - 2 * (rot_quat.y * rot_quat.y) - 2 * (rot_quat.z * rot_quat.z);
            mat[0][1] = 2 * (rot_quat.x * rot_quat.y + rot_quat.z * rot_quat.w);
            mat[0][2] = 2 * (rot_quat.z * rot_quat.x - rot_quat.y * rot_quat.w);
            mat[1][0] = 2 * (rot_quat.x * rot_quat.y - rot_quat.z * rot_quat.w);
            mat[1][1] = 1 - 2 * (rot_quat.z * rot_quat.z) - 2 * (rot_quat.x * rot_quat.x);
            mat[1][2] = 2 * (rot_quat.y * rot_quat.z + rot_quat.x * rot_quat.w);
            mat[2][0] = 2 * (rot_quat.z * rot_quat.x + rot_quat.y * rot_quat.w);
            mat[2][1] = 2 * (rot_quat.y * rot_quat.z - rot_quat.x * rot_quat.w);
            mat[2][2] = 1 - 2 * (rot_quat.x * rot_quat.x) - 2 * (rot_quat.y * rot_quat.y);
        }
        template<typename T>
        void create_transform_rotation(Matrix<T, 3, 3>& mat, const Quaternion<T>& rot_quat) {
            mat = Matrix<T, 3, 3>(constants::one<T>);
            mat[0][0] = 1 - 2 * (rot_quat.y * rot_quat.y) - 2 * (rot_quat.z * rot_quat.z);
            mat[0][1] = 2 * (rot_quat.x * rot_quat.y + rot_quat.z * rot_quat.w);
            mat[0][2] = 2 * (rot_quat.z * rot_quat.x - rot_quat.y * rot_quat.w);
            mat[1][0] = 2 * (rot_quat.x * rot_quat.y - rot_quat.z * rot_quat.w);
            mat[1][1] = 1 - 2 * (rot_quat.z * rot_quat.z) - 2 * (rot_quat.x * rot_quat.x);
            mat[1][2] = 2 * (rot_quat.y * rot_quat.z + rot_quat.x * rot_quat.w);
            mat[2][0] = 2 * (rot_quat.z * rot_quat.x + rot_quat.y * rot_quat.w);
            mat[2][1] = 2 * (rot_quat.y * rot_quat.z - rot_quat.x * rot_quat.w);
            mat[2][2] = 1 - 2 * (rot_quat.x * rot_quat.x) - 2 * (rot_quat.y * rot_quat.y);
        }

        template<typename T>
        void create_transform_scale(Matrix<T, 4, 4>& mat, T x_scale, T y_scale, T z_scale) {
            mat = Matrix<T, 4, 4>(x_scale, y_scale, z_scale, constants::one<T>);
        }
        template<typename T>
        void create_transform_scale(Matrix<T, 4, 4>& mat, const Vector<T, 3>& scale_vec) {
            mat = Matrix<T, 4, 4>(scale_vec.x, scale_vec.y, scale_vec.z, constants::one<T>);
        }

        template<typename T>
        void create_transform_translate(Matrix<T, 4, 4>& mat, T x_trans, T y_trans, T z_trans) {
            mat = Matrix<T, 4, 4>(constants::one<T>);
            mat.c_14 = x_trans;
            mat.c_24 = y_trans;
            mat.c_34 = z_trans;
        }
        template<typename T>
        void create_transform_translate(Matrix<T, 4, 4>& mat, const Vector<T, 3>& trans_vec) {
            mat = Matrix<T, 4, 4>(constants::one<T>);
            mat.c_14 = trans_vec.x;
            mat.c_24 = trans_vec.y;
            mat.c_34 = trans_vec.z;
        }

        // Basic order of arguments is always rotation,translation,scale
        // If any component is missed, it is assumed "identity"
        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, const Matrix<T, 4, 4>& rot_mat, const Matrix<T, 4, 4>& trans_mat, const Matrix<T, 4, 4>& scale_mat) {
            mat = mul(mul(trans_mat, rot_mat), scale_mat);
        }
        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, const Matrix<T, 4, 4>& rot_mat, const Matrix<T, 4, 4>& trans_mat) {
            mat = mul(trans_mat, rot_mat);
        }

        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, T rot_yaw, T rot_pitch, T rot_roll, const Vector<T, 3>& trans_vec, const Vector<T, 3>& scale_vec) {
            Matrix<T, 4, 4> rot_mat, trans_mat, scale_mat;

            create_transform_rotation(rot_mat, rot_yaw, rot_pitch, rot_roll);
            create_transform_translate(trans_mat, trans_vec);
            create_transform_scale(scale_mat, scale_vec);

            create_transform(mat, rot_mat, trans_mat, scale_mat);
        }
        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, const Matrix<T, 3, 3>& rot_mat3, const Vector<T, 3>& trans_vec, const Vector<T, 3>& scale_vec) {
            Matrix<T, 4, 4> trans_mat, scale_mat;

            Matrix<T, 4, 4> rot_mat(rot_mat3);
            create_transform_translate(trans_mat, trans_vec);
            create_transform_scale(scale_mat, scale_vec);

            create_transform(mat, rot_mat, trans_mat, scale_mat);
        }
        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, const Quaternion<T>& rot_quat, const Vector<T, 3>& trans_vec, const Vector<T, 3>& scale_vec) {
            Matrix<T, 4, 4> rot_mat, trans_mat, scale_mat;

            create_transform_rotation(rot_mat, rot_quat);
            create_transform_translate(trans_mat, trans_vec);
            create_transform_scale(scale_mat, scale_vec);

            create_transform(mat, rot_mat, trans_mat, scale_mat);
        }

        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, T rot_yaw, T rot_pitch, T rot_roll, const Vector<T, 3>& trans_vec) {
            Matrix<T, 4, 4> rot_mat, trans_mat;

            create_transform_rotation(rot_mat, rot_yaw, rot_pitch, rot_roll);
            create_transform_translate(trans_mat, trans_vec);

            create_transform(mat, rot_mat, trans_mat);
        }
        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, const Matrix<T, 3, 3>& rot_mat3, const Vector<T, 3>& trans_vec) {
            Matrix<T, 4, 4> trans_mat;

            Matrix<T, 4, 4> rot_mat(rot_mat3);
            create_transform_translate(trans_mat, trans_vec);

            create_transform(mat, rot_mat, trans_mat);
        }
        template<typename T>
        void create_transform(Matrix<T, 4, 4>& mat, const Quaternion<T>& rot_quat, const Vector<T, 3>& trans_vec) {
            Matrix<T, 4, 4> rot_mat, trans_mat;

            create_transform_rotation(rot_mat, rot_quat);
            create_transform_translate(trans_mat, trans_vec);

            create_transform(mat, rot_mat, trans_mat);
        }

        //template<typename T>
        //void create_transform(Matrix<T, 4, 4>& mat, const Matrix<T, 3, 3>& rot_mat3, const Vector<T, 3>& trans_vec) {}
        //template<typename T>
        //void create_transform(Matrix<T, 4, 4>& mat, const Quaternion<T>& rot_quat, const Vector<T, 3>& trans_vec) {}


        // Decompose 4x4 transformations into their components
        //math::Decompose(transformComponent->Transform, position, Forward, Right, Up, yaw, pitch, scale);
	
        template<typename T>
        bool decompose(const Matrix<T, 4, 4>& transform,
                       Matrix<T, 3, 3>& rot_mat, Vector<T, 3>& trans_vec, Vector<T, 3>& scale_vec) {

            Matrix<T, 4, 4> local_matrix(transform); // local copy
            //ENGINE_LOG_DEBUG("local_matrix = {0}", local_matrix);

            // first check if mat[3][3] != 0;
            double eps = 1e-10;
            if (laml::epsilon_equal(local_matrix.c_44, 0.0, eps)) {
                return false;
            }

            // assume matrix is already "normalized" i.e. w=1.0
            if (!laml::epsilon_equal(local_matrix.c_44, 1.0, eps)) {
                //assert(laml::epsilon_equal(local_matrix.c_44, 1.0, eps) && "Transformation matrix non-standard!");
                local_matrix = local_matrix / local_matrix.c_44;
            }

            // Ignore perspective
            assert(
                epsilon_equal(local_matrix.c_41, 0.0, eps) &&
                epsilon_equal(local_matrix.c_42, 0.0, eps) &&
                epsilon_equal(local_matrix.c_43, 0.0, eps) &&
                "Transformation has perspective elements!");

            // extract Translation
            trans_vec.x = local_matrix.c_14;
            trans_vec.y = local_matrix.c_24;
            trans_vec.z = local_matrix.c_34;

            local_matrix.c_14 = constants::zero<T>;
            local_matrix.c_24 = constants::zero<T>;
            local_matrix.c_34 = constants::zero<T>;

            //ENGINE_LOG_DEBUG("pos_vec = {0}", trans_vec);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", local_matrix);

            // extract scale and shear
            Matrix<T, 3, 3> mat = laml::minor(local_matrix, 3, 3);

            // compute x scale factor and normalize first column
            scale_vec.x = laml::length(mat._cols[0]);
            mat._cols[0] = laml::normalize(mat._cols[0]);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            // compute y scale factor and normalize second column
            scale_vec.y = laml::length(mat._cols[1]);
            mat._cols[1] = laml::normalize(mat._cols[1]);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            // compute z scale factor and normalize third column
            scale_vec.z = laml::length(mat._cols[2]);
            mat._cols[2] = laml::normalize(mat._cols[2]);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            //ENGINE_LOG_DEBUG("scale_vec = {0}", scale_vec);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            // what remains should be a pure rotation 3x3!
            //ENGINE_LOG_DEBUG("rot_33 = {0}", mat);
            rot_mat = mat;

            return true;
        }

        template<typename T>
        void decompose(const Matrix<T, 4, 4>& mat,
                       Vector<T, 3>& trans_vec,
                       Vector<T, 3>& forward_vec, Vector<T, 3>& right_vec, Vector<T, 3>& up_vec,
                       T& rot_yaw, T& rot_pitch, T& rot_roll,
                       Vector<T, 3>& scale_vec) {

            Matrix<T, 3, 3> rot_mat;
            //Vector<T, 3> trans_vec;
            //Vector<T, 3> scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // Right: +X
            right_vec.x = rot_mat.c_11;
            right_vec.y = rot_mat.c_21;
            right_vec.z = rot_mat.c_31;
            // Up: +Y
            up_vec.x = rot_mat.c_12;
            up_vec.y = rot_mat.c_22;
            up_vec.z = rot_mat.c_32;
            // Forward: -Z
            forward_vec.x = -rot_mat.c_13;
            forward_vec.y = -rot_mat.c_23;
            forward_vec.z = -rot_mat.c_33;

            // ypr
            rot_pitch = asin(-rot_mat.c_23) * constants::rad2deg<T>;
            rot_yaw = atan2(rot_mat.c_13, rot_mat.c_33) * constants::rad2deg<T>;
            rot_roll = atan2(-rot_mat.c_21, rot_mat.c_22) * constants::rad2deg<T>;
        }

        template<typename T>
        void decompose(const Matrix<T, 4, 4>& mat,
                       Vector<T, 3>& trans_vec,
                       Vector<T, 3>& forward_vec, Vector<T, 3>& right_vec, Vector<T, 3>& up_vec,
                       T& rot_yaw, T& rot_pitch,
                       Vector<T, 3>& scale_vec) {

            Matrix<T, 3, 3> rot_mat;
            //Vector<T, 3> trans_vec;
            //Vector<T, 3> scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // Right: +X
            right_vec.x = rot_mat.c_11;
            right_vec.y = rot_mat.c_21;
            right_vec.z = rot_mat.c_31;
            // Up: +Y
            up_vec.x = rot_mat.c_12;
            up_vec.y = rot_mat.c_22;
            up_vec.z = rot_mat.c_32;
            // Forward: -Z
            forward_vec.x = -rot_mat.c_13;
            forward_vec.y = -rot_mat.c_23;
            forward_vec.z = -rot_mat.c_33;

            // ypr
            rot_pitch = asin(-rot_mat.c_23) * constants::rad2deg<T>;
            rot_yaw = atan2(rot_mat.c_13, rot_mat.c_33) * constants::rad2deg<T>;
        }

        template<typename T>
        void decompose(const Matrix<T, 4, 4>& mat,
                       Vector<T, 3>& forward_vec, Vector<T, 3>& right_vec, Vector<T, 3>& up_vec) {

            Matrix<T, 3, 3> rot_mat;
            Vector<T, 3> trans_vec;
            Vector<T, 3> scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // Right: +X
            right_vec.x = rot_mat.c_11;
            right_vec.y = rot_mat.c_21;
            right_vec.z = rot_mat.c_31;
            // Up: +Y
            up_vec.x = rot_mat.c_12;
            up_vec.y = rot_mat.c_22;
            up_vec.z = rot_mat.c_32;
            // Forward: -Z
            forward_vec.x = -rot_mat.c_13;
            forward_vec.y = -rot_mat.c_23;
            forward_vec.z = -rot_mat.c_33;
        }

        template<typename T>
        void decompose(const Matrix<T, 4, 4>& mat,
                       T& rot_yaw, T& rot_pitch, T& rot_roll) {

            Matrix<T, 3, 3> rot_mat;
            Vector<T, 3> trans_vec;
            Vector<T, 3> scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // ypr
            rot_pitch = asin(-rot_mat.c_23) * constants::rad2deg<T>;
            rot_yaw = atan2(rot_mat.c_13, rot_mat.c_33) * constants::rad2deg<T>;
            rot_roll = atan2(-rot_mat.c_21, rot_mat.c_22) * constants::rad2deg<T>;
        }

        template<typename T>
        void lookAt(Matrix<T,4,4>& result, const Vector<T,3>& eye, const Vector<T,3>& center, const Vector<T,3>& up) {
            Vector<T,3> f = laml::normalize(center - eye);
            Vector<T,3> u = laml::normalize(up);
            Vector<T,3> s = laml::normalize(laml::cross(f, u));
            u = laml::cross(s, f);

            laml::identity(result);
            result.c_11 = s.x;
            result.c_21 = s.y;
            result.c_31 = s.z;

            result.c_12 = u.x;
            result.c_22 = u.y;
            result.c_32 = u.z;

            result.c_13 = -f.x;
            result.c_23 = -f.y;
            result.c_33 = -f.z;

            result.c_14 = -laml::dot(s, eye);
            result.c_14 = -laml::dot(u, eye);
            result.c_14 =  laml::dot(f, eye);
        }
    }
}

#endif